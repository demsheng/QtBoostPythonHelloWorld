#define BOOST_BIND_GLOBAL_PLACEHOLDERS

//它可以让VC在编译时的output窗口中输出程序具体链接了哪些boost库以及链接顺序。
#define BOOST_LIB_DIAGNOSTIC

//告诉boost禁用自动链接。
#define BOOST_ALL_NO_LIB

#define BOOST_PYTHON_STATIC_LIB

#include<string>
#include<boost/python.hpp>


using namespace std;
using namespace boost::python;

char const * greet()
{
    return "hello,world";
}

BOOST_PYTHON_MODULE(hello)
{
    def("greet", greet);
}
