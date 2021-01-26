#define BOOST_BIND_GLOBAL_PLACEHOLDERS
//#include<iostream>
//#include<stdio.h>
//
//#include<boost\version.hpp> //包含boost头文件
//#include<boost\config.hpp>
//
//int main()
//{
//	using namespace std;
//	cout << BOOST_VERSION << endl;
//	cout << BOOST_LIB_VERSION << endl;
//	cout << BOOST_PLATFORM << endl;
//	cout << BOOST_COMPILER << endl;
//	cout << BOOST_STDLIB << endl;
//
//	system("pause");
//	return 0;
//}
//#include <boost/bind/bind.hpp>

#include <boost/python.hpp>
#include<iostream>
#include<stdio.h>

//using namespace boost::placeholders;

using namespace boost::python;
#define BOOST_PYTHON_STATIC_LIB

char const* greet()
{
    return "hello, world";
}


BOOST_PYTHON_MODULE(helloworld)			// Python 模块开始
{
    using namespace boost::python;		// 打开命名空间
    def("greet", greet);
}
