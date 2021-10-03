#ifndef __CSHELLO__
#define __CSHELLO__

#include <string>
#include <iostream>



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

#endif
