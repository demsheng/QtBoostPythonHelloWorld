
#define BOOST_BIND_GLOBAL_PLACEHOLDERS

//它可以让VC在编译时的output窗口中输出程序具体链接了哪些boost库以及链接顺序。
#define BOOST_LIB_DIAGNOSTIC

//告诉boost禁用自动链接。
#define BOOST_ALL_NO_LIB

#define BOOST_PYTHON_STATIC_LIB

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
