

#define BOOST_BIND_GLOBAL_PLACEHOLDERS

//它可以让VC在编译时的output窗口中输出程序具体链接了哪些boost库以及链接顺序。
#define BOOST_LIB_DIAGNOSTIC

//告诉boost禁用自动链接。
#define BOOST_ALL_NO_LIB

#define BOOST_PYTHON_STATIC_LIB

#include <iostream>
using namespace std;
#include <boost/python.hpp>
using namespace boost::python;

int main() //(int argc, char *argv[])
{
    Py_Initialize();

    object main_module = import("__main__");
    object main_namespace = main_module.attr("__dict__");

    //1 exec 执行一个语句
    exec("hello = open('hello.txt', 'w')\n"
       "hello.write('Hello world!')\n"
       "hello.close()\n",
       main_namespace);
    exec("print('hello.txt', flush=True)\n",
       main_namespace);
    exec("result = 5 ** 2", main_namespace);
    int five_squared = extract<int>(main_namespace["result"]);
    cout << "The five_squeared caculated by python is " << five_squared << endl;

    // Load the sys module.
    object sys = import("sys");

    // Extract the python version.
    std::string version = extract<std::string>(sys.attr("version"));
    std::cout << version << std::endl;


    //要求simple.py与可执行文件在相同路径下! 运行ok
    object simple = exec_file("simple.py",main_namespace, main_namespace);
    //object simple = exec_file("F:\\MyProgram\\QtProject\\QtBoostPythonHelloWorld\\ex1_5_execfile\\simple.py",main_namespace, main_namespace);
    //dict global;
    //object result = exec_file("simple.py", global, global);
    object foo = main_namespace["foo"];
    int val = extract<int>(foo(5));
    cout << "Python has caculated foo as " << val << endl;

    return 0;
}
