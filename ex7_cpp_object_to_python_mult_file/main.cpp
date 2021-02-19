

#define BOOST_BIND_GLOBAL_PLACEHOLDERS

//它可以让VC在编译时的output窗口中输出程序具体链接了哪些boost库以及链接顺序。
#define BOOST_LIB_DIAGNOSTIC

//告诉boost禁用自动链接。
#define BOOST_ALL_NO_LIB

#define BOOST_PYTHON_STATIC_LIB

#include <boost/python.hpp>
#include <string>
#include <iostream>

#include "hello.h"

using namespace boost::python;
using namespace std;

BOOST_PYTHON_MODULE(hello)
{
    class_<World>("World")
        .def(init<std::string>())
        .def("greet", &World::greet)
        .def("set", &World::set)
    ;
};

typedef boost::shared_ptr< World > world_ptr;

int main()//int argc, char **argv)
{
    Py_Initialize();
    try {
        PyRun_SimpleString(
            "class Person:\n"
            "    def sayHi(self):\n"
            "        print ('hello from python', flush=True)\n"
            "    def greetReset(self, instance):\n"
            "        instance.set('Python')\n"
          );

        world_ptr worldObjectPtr (new World);
        worldObjectPtr->set("C++!");

        //inithello(); //python2
        PyInit_hello(); //python3

        object o_main 
            = object(handle<>(borrowed(PyImport_AddModule("__main__"))));
        object o_person_type = o_main.attr("Person");
        object o_person = o_person_type();
        object o_func1 = o_person.attr("sayHi");
        o_func1();
        object o_func2 = o_person.attr("greetReset");
        o_func2(boost::python::ptr(worldObjectPtr.get()));
        worldObjectPtr->greet();


    }
    catch (error_already_set) {
        PyErr_Print();
    }

    Py_Finalize();

    return 0;
}
