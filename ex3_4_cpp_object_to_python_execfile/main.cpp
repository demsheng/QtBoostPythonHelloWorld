

#define BOOST_BIND_GLOBAL_PLACEHOLDERS

//它可以让VC在编译时的output窗口中输出程序具体链接了哪些boost库以及链接顺序。
#define BOOST_LIB_DIAGNOSTIC

//告诉boost禁用自动链接。
#define BOOST_ALL_NO_LIB

#define BOOST_PYTHON_STATIC_LIB

#include <iostream>
#include <vector>
#include <tuple>
#include <boost/python.hpp>
#include <boost/python/list.hpp>



#include <boost/python.hpp>
#include <iostream>

using namespace std;
using namespace boost::python;

class World
{
    public:
    void set(std::string msg) { this->msg = msg; }
    std::string greet() { return msg; }
    std::string msg;
};

typedef boost::shared_ptr< World > world_ptr;

BOOST_PYTHON_MODULE(hello)
{
    class_<World>("World")
        .def("greet", &World::greet)
        .def("set", &World::set)
        ;

    register_ptr_to_python<world_ptr>();
}

int main()//int argc, char *argv[])
{

    Py_Initialize();

    world_ptr worldObjectPtr (new World);
    worldObjectPtr->set("Hello from C++!");

    try {
        PyInit_hello();
        //PyRun_SimpleString("import hello");
        //PyRun_SimpleString("from hello import *");

        object module(handle<>(borrowed(PyImport_AddModule("__main__"))));
        object dictionary = module.attr("__dict__");

        dictionary["pyWorldObjectPtr"] = worldObjectPtr;
        PyRun_SimpleString("pyWorldObjectPtr.set('Hello from Python!')");

    } catch (error_already_set) {
        PyErr_Print();
    }

    std::cout << "worldObjectPtr->greet(): " << worldObjectPtr->greet() <<
    std::endl;

    Py_Finalize();

    return 0;
}
