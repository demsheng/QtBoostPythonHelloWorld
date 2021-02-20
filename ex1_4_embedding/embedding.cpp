

#define BOOST_BIND_GLOBAL_PLACEHOLDERS

//它可以让VC在编译时的output窗口中输出程序具体链接了哪些boost库以及链接顺序。
#define BOOST_LIB_DIAGNOSTIC

//告诉boost禁用自动链接。
#define BOOST_ALL_NO_LIB

#define BOOST_PYTHON_STATIC_LIB

#include <iostream>
#include <string>
#include <boost/python.hpp>
using namespace boost::python;

void running_python_code(const char *code)
{
		object main_module = import("__main__");
		object main_namespace = main_module.attr("__dict__");
		object result = exec(code, main_namespace);
}

void get_result()
{
		int five_squared;

		object main_module = import("__main__");
		object main_namespace = main_module.attr("__dict__");
		// method 1
		object ignored = exec("result = 5 ** 2", main_namespace);
		five_squared = extract<int>(main_namespace["result"]);
		std::cout << "In cpp, method 1, five_squared: " << five_squared << std::endl;
		// method 2
		object result = eval("5 ** 2");
		five_squared = extract<int>(result);
		std::cout << "In cpp, method 2, five_squared: " << five_squared << std::endl;
}

void exception_handling()
{
		try
		{
				object result = eval("5/0");
				std::cout << "I will never be printed" << std::endl;
		}
		catch (error_already_set const &)
		{
				if (PyErr_ExceptionMatches(PyExc_ZeroDivisionError))
				{
						std::cout << "catch ZeroDivisionError in cpp" << std::endl;
						PyErr_Print();
				}
				else
						PyErr_Print();
		}
}

void sleep_for_20_seconds()
{
		object main_module = import("__main__");
		object main_namespace = main_module.attr("__dict__");
        exec("print(\"In python, going to sleep for 10 seconds\", flush=True)\n"
			 "import time\n"
             "time.sleep(10)", main_namespace);
		
}

int main()
{
		Py_Initialize();
		running_python_code("import sys\n"
                        "print(\"I am called from cpp\", flush=True)\n"
                        "print(\"sys.version: \", sys.version, flush=True)");
        get_result();
        exception_handling();
        sleep_for_20_seconds();
		return 0;
}
