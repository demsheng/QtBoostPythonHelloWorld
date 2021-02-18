# boost.python笔记
标签：boost.python

## 简介
### Boost.python是什么？
它是boost库的一部分，随boost一起安装，用来实现C++和Python代码的交互。

### 使用Boost.python有什么特点？
不需要修改原有的C++代码，支持比较丰富的C++特性。不会生成额外的python代码（像SWIG那样），但是需要写一部分C++的封装代码。

我只用到了其功能的一部分，把C/C++实现的功能封装为可供python直接调用的.so库。具体场景是，有一个C++模块通过thrift封装为RPC，python代码通过PRC调用请求服务。由于调用频次较多，RPC调用开销成为一个很耗时的部分，因此想直接通过python对原模块功能进行调用。

以前了解SWIG可以实现这个需求。本已开始看SWIG的文档，但突然又想看一下还有没有别的方法，于是在stack overflow上搜了一些问题，发现不少人推荐Boost.python，于是打算拿它来试一试。

## 如何使用Boost.python
首先，前提是安装了开发环境。

1. 安装了boost开发环境。安装了头文件和动态库。  
2. 安装了python开发环境。安装了头文件和动态库。

然后，就是写代码了，这是个没办法避免的事情！！！

需要自己动手的有两个地方。一个是xxxxxx_wrapper.cpp文件，文件名无所谓，其核心目的是定义导出的python模块的名称，以及需要导出的类、函数等。另一个是需要修改一下你的Makefile，来编译、链接这个so库。

先来看一下xxxxxx_wrapper.cpp。一般情况下，它的内容跟下面的代码比较接近。
```
#include <boost/python.hpp>
// 其他需要包含的头文件，与具体业务有关

namespace py = boost::python;

// 其他函数，可能包括一些用于类型转换和封装的

BOOST_PYTHON_MODULE(my_module_name)
{
    // 导出普通函数
    def("fun_name_in_python", &fun_name_in_c);
    
    // 导出类及部分成员
    class_<ClassNameInCpp>("ClassNameInPython", init<std::string>())               //类名，默认构造函数
        .def(init<double>())                                                       //其他构造函数
        .def("memberFunNameInPython", &ClassNameInCpp::memberFunNameInCpp)         //成员函数
        .def_readwrite("dataMemberInPython", &ClassNameInCpp::dataMemberInCpp)     //普通成员变量
        .def_readonly("dataMemberInPython_2", &ClassNameInCpp::dataMemberInCpp_2)  //只读成员变量
    ;
}
```
这个文件的核心目的体现在BOOST_PYTHON_MODULE里，定义需要导出给python的东西。

在Makefile里，需要增加一条用来编译导出的.so的规则，编译命令里通用的部分一般像下面这样，这里把编译和链接写在一起了。
```
g++ -o my_module_name.so -shared -fPIC -I${BOOST_INCLUDE_PATH} -I${PYTHON_INCLUDE_PATH} -L${BOOST_LIB_DIR} -lboost_python ${MY_SRC_FILES}
```
编译及链接参数的作用如下，其他参数由具体项目的业务逻辑决定：

1. -o my_module_name.so，这里的模块名需要和xxxxxx_wrapper.cpp文件里BOOST_PYTHON_MODULE(my_module_name)一致；
2. -I${BOOST_INCLUDE_PATH} -I${PYTHON_INCLUDE_PATH}是编译需要的；
3. -L${BOOST_LIB_DIR} -lboost_python -shared -fPIC是链接需要的；
4. ${MY_SRC_FILES}包含了xxxxxxx_wrapper.cpp以及业务逻辑需要的其他.cpp，.c文件；  

**至此，我们便有了my_module_name.so这个可以被python调用的模块了。** 测试一下吧。

```
>>>import my_moduel_name
>>>help(my_module_name)
```

可以看到被导出的类及函数，然后可以按照python的习惯来使用这些类和函数了。

## 如何写wrapper
以一个实例为框架来解释吧，内容包括普通函数、类、数据成员、成员函数、通过参数传递结果、容器。其他特性没有用到，也没有测试。

先来看一下业务逻辑的代码。包含一个类，一个以类对象为参数的函数，一个通过引用修改类对象的函数。
```
//test_class.h

// 定义一个类
class A
{
    public:
        A(){privateVal=0;}                      //默认构造函数
        A(int val){privateVal=val;}             //带参数的构造函数
        void set(int val){privateVal=val;}      //成员函数
        int get() const {return privateVal;};   //成员函数
        int publicVal;                          //公共数据成员
    private:
        int privateVal;                         //私有数据成员
};

int addA(A &a, int addVal);                   //普通函数，有返回值，通过引用修改参数
void printA(const A& a);
```

```
//test_class.cpp
#include <stdio.h>
#include "test_class.h"

int addA(A &a, int addVal)
{
    int val = a.get();
    val += addVal;
    a.set(val);
    return val;
}
void printA(const A& a)
{
    printf("%d\n", a.get());
}
```

然后是wrapper.cpp文件，这里实际名为test_class_wrapper.cpp。

```
//test_class_wrapper.cpp
#include <boost/python.hpp>
#include "test_class.h"

BOOST_PYTHON_MODULE(test_class)
{
    using namespace boost::python;
    // 导出类
    class_<A>("A", init<>())                            //如果默认构造函数没有参数，可以省略
        .def(init<int>())                               //其他构造函数
        .def("get", &A::get)                            //成员函数
        .def("set", &A::set)                            //成员函数
        .def_readwrite("publicVal", &A::publicVal)      //数据成员，当然是公共的
    ;   
    def("printA", &printA);
    def("addA", &addA);
}
```

通过python命令行测试一下

```
>>>import test_class
>>>a = test_class.A(5)
>>>ret = addA(a, 10)
>>>print ret
15
>>>print a.get()
15
```

到目前为止，整个过程都很顺利。需要额外写的代码很少，也很规整，与某种IDL的写法接近，只需要“声明”一下，剩下的事情都交给编译器及库完成。但有的时候，这个过程就不这么顺利了，我们需要额外写一些转换及封装。比如在这一部分最开始提到的容器，上面的代码就没有涉及。

下面的代码，我们对上面的例子做了一些扩展。第一，对类A增加了一个vector成员，需要在python代码里引用该成员；第二，增加了一个函数，以vector为参数，需要在python代码里直接调用该函数。下面我们就来解释与容器有关的导出。

```
#include<vector>

class B;

class A
{
    public:
        A(){privateVal=0;}                      //默认构造函数
        A(int val){privateVal=val;}             //带参数的构造函数
        void set(int val){privateVal=val;}      //成员函数
        int get() const {return privateVal;};   //成员函数
        int publicVal;                          //公共数据成员
        std::vector<B> m_vB;
    private:
        int privateVal;                           //私有数据成员
};

class B
{
    public:
        B(){}
        ~B(){}
        int pos;
        int len;
};

int accumulate(const std::vector<A>& v_A);
int addA(A &a, int addVal);                   //普通函数，有返回值，通过引用修改参数
void printA(const A& a); 
```

```
#include <stdio.h>
#include "test_class.h"

int addA(A &a, int addVal)
{
    int val = a.get();
    val += addVal;
    a.set(val);
    return val;
}
void printA(const A& a)
{
    printf("%d\n", a.get());
}

int accumulate(const std::vector<A>& v_A)
{
    int ret = 0;
    for (size_t i = 0; i < v_A.size(); i++)
    {   
        ret += v_A[i].get();
    }   
    return ret;
}
```

首先，需要明白一点，c++中的vector不等于python中的list，虽然它们看上去比较相似。Boost.python中有与python的list对应的东西，是boost::python::list，如果在python代码里以list为参数调用某个方法，则在c++代码中这个参数被自动映射为boost::python::list，不是vector。既然这样，如果我们不打算修改原有的C++代码，又想调用以vector为参数的函数，该怎么办呢？

目前我了解的方法由两种：

1. 在C++代码里对以vector为参数的函数进行一层封装，封装为以boost::python::list为参数的函数，导出封装后的函数。在函数里通过boost::python::extract_<T>对list里的所有成员进行提取，将其由boost::python::object对象变为T类型的对象，然后存于vector<T>中，再调用以vector<T>为参数的函数。
如果需要返回list或者原函数对vector参数的内容作了修改，需要再将调用函数后的vector内的每个元素放回list里。
2. 直接导出vector<T>类型。此时vector<T>本身作为一个类型被导出给python代码，与普通的类具有同等地位。但是，与普通类不同的是，它通过模板vector_indexing_suite<std::vector<T> >()导出，自动实现了append，slice，__len__等方法，在python里可以像使用list那样操作这个被导出的vector类。而且，以vector<T>为参数的函数，在通过def导出给python时，其参数会被自动映射为vector_indexing_suite<std::vector<T> >。同理，python代码传入的通过vector_indexing_suite导出的容器对象，也会在c++代码里被自动转换为vector，这里无需显式地写转换函数。

下面的代码是wrapper文件，使用第二种方法，即直接导出vector类型。

为什么这么做呢？因为A里有个vector成员，要导出这个成员，必须导出这个`vector<B>`这个类型，否则还需要对类A再做一层封装，让它包含一个boost::python::list成员，这就太麻烦了。

```
#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include "test_class.h"

bool operator==(const B& left, const B& right);

bool operator==(const A& left, const A& right)
{
    if (left.get() != right.get() || left.publicVal != right.publicVal)
        return false;
    if (left.m_vB.size() != right.m_vB.size())
        return false;
    for (size_t i = 0; i < left.m_vB.size(); i ++) 
    {   
        if (!(left.m_vB[i] == right.m_vB[i]))
            return false;
    }   
    return true;
}

bool operator==(const B& left, const B& right)
{
    return (left.pos == right.pos && left.len == right.len);
}

BOOST_PYTHON_MODULE(test_class)
{
    using namespace boost::python;
    class_<A>("A", init<>())                            //如果默认构造函数没有参数，可以省略
        .def(init<int>())                               //其他构造函数
        .def("get", &A::get)                            //成员函数
        .def("set", &A::set)                            //成员函数
        .def_readwrite("publicVal", &A::publicVal)      //数据成员，当然是公共的
        .def_readwrite("vB", &A::m_vB)
        ;   
    class_<std::vector<A> >("VecA")
        .def(vector_indexing_suite<std::vector<A> >())
        ;   
    class_<B>("B")
        .def_readwrite("pos", &B::pos)
        .def_readwrite("len", &B::len)
        ;   
    class_<std::vector<B> >("VecB")
        .def(vector_indexing_suite<std::vector<B> >())
        ;   
    def("printA", &printA);
    def("addA", &addA);
    def("accumulate", &accumulate);
}
```

我们还是从BOOST_PYTHON_MODULE内的代码开始看。

- `class_<A>`的定义看上去和前面的例子没有太大差别，只是多导出了一个成员.def_readwrite("vB", &A::m_vB)。即使这个成员变量是`vector<B>`类型的，在这里也不需要特殊对待；
- `class_<B>`就是导出一个类，包含两个共有数据成员。这里也没什么特别的；
- `class_<std::vector<A> >("VecA")`和`class_<std::vector<B> >("VecB")`是本例的重点，导出了两个不同的vector类型，因为在c++里，vector是一个类模板，`vector<A>`和`vector<B>`才是两个具体的类型；
- printA，addA，accumulate是三个导出的函数。即使其参数是`vector<A>`类型，也无需特别对待；

除此之外，注意到为类型A和类型B定义了==操作符，这是boost.python在导出某种类型的vector时需要的，在内部某个地方用到了==操作符。**如果仅导出类型，不导出类型的向量，是不需要==操作符的，如前面的例子所示。**

编译链接后，通过python命令行测试一下：

```
>>>import test_class
>>>a1 = test_class.A()
>>>b1 = test_class.B()    # 实例化一个B
>>>b1.pos = 1
>>>b1.len = 1
>>>b2 = test_class.B()    # 实例化另一个B
>>>b2.pos = 2
>>>b2.len = 2
>>>a1.vB.append(b1)      # a1.vB是vector<B>在python中对应类型的对象，接口类似list，但只能添加B类型的对象
>>>a1.vB.append(b2)
>>>print a1.vB[-1].len        # a1.vB支持list的下标引用
2
>>>a1.set(1)
>>>a2 = test_class.A(2)
>>>a3 = test_class.A(3)
>>>vA = test_class.VecA()    # vector<A>在python中对应的类型
>>>vA.append(a1)
>>>vA.append(a2)
>>>vA.append(a3)
>>>print accumulate(vA)      # 调用以vector<A>为参数的函数
6
```

对于导出的python模块来说，一切在python中会被引用到的变量，其所属类型（基本数据类型除外）都需要被明确导出，也就是都需要在BOOST_PYTHON_MODULE里被定义。如本例中的`vector<B>`，尽管没有函数以该类型为参数，但如果想要在python代码里引用A的成员vB，就需要导出它，否则会抛异常。相反，如果不需要在python代码里引用这个成员，则不需要导出`vector<B>`这个类型，而且在`class_<A>`的定义中也应把.def_readwrite("vB", &A::m_vB)去掉。如果不导出`vector<B>`类型，但在`class_<A>`的定义中通过.def_readwrite("vB", &A::m_vB)导出了该成员，编译不会出问题，使用python模块也不会出问题，但只要代码引用到A.vB就会抛异常，相当于埋了一个坑。

从实用的角度看，这样一个流程可能会比较有效。首先，确定需要导出的函数及类型。然后检查函数（包括成员函数）参数及返回值的类型，非基本类型需要被导出；检查导出的类成员变量，如果不是基本类型，其类型也要导出。如此直到没有新的类型需要被添加为止。

## 总结
Boost.python的文档感觉比较少，很多问题和trick都是在stack overflow上看到然后再试验的。据了解，Boost.python支持更为丰富的c++特性，这里只用到了一小部分。  

作者：terencezhou
链接：https://www.jianshu.com/p/0fee49c58caa
来源：简书
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。