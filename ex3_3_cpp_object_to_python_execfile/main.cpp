

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

class PyData
{
    public:

    PyData() {}

    float m_slope;
    float m_compliance;

    boost::python::tuple    m_TORSO_LV;
    boost::python::list     m_DsOsAVS;
    boost::python::list     m_RF_FORCES;
    boost::python::list     m_LF_FORCES;

    void InitData()
    {
        // simulate setting up data
        m_slope = 1.0;
        m_compliance = 2.0;

        m_TORSO_LV = boost::python::make_tuple(3.0, 4.0, 5.0);

        m_DsOsAVS.append(boost::python::make_tuple(10.0, 11.0, 12.0));
        m_DsOsAVS.append(boost::python::make_tuple(20.0, 21.0, 22.0));

        // etc.
    }

    ~PyData() {}
};

BOOST_PYTHON_MODULE(pydata) {
boost::python::class_<PyData>("PyData")
    .def_readwrite("Torso_LV", &PyData::m_TORSO_LV)
    .def_readwrite("DsOsAVs", &PyData::m_DsOsAVS)
    .def_readwrite("RF_FORCES", &PyData::m_RF_FORCES)
    .def_readwrite("LF_FORCES", &PyData::m_LF_FORCES)
    .def_readwrite("slope", &PyData::m_slope)
    .def_readwrite("compliance", &PyData::m_compliance)
    ;
};

using namespace boost::python;

int main ()//int argc, char * argv[])
{
    std::cout << "main begin " << std::endl;
    Py_Initialize();

    //initpydata();
    PyInit_pydata();

    boost::python::object main=boost::python::import("__main__");
    boost::python::object global(main.attr("__dict__"));
    std::cout << "main2 " << std::endl;
    boost::python::object result = boost::python::exec_file("Python3.py", global, global);
//    PyRun_SimpleString(
//"def predict_on_data(o):\n"
//"    print ('In Python:', flush=True)\n"
//      );
    std::cout << "main3 " << std::endl;
    boost::python::object predict_on_data = global["predict_on_data"];
    if (!predict_on_data.is_none())
    {
        boost::shared_ptr<PyData> o(new PyData);
        o->InitData();
        predict_on_data(boost::python::ptr(o.get()));
        std::cout << "values in c++ object are now: " << o->m_slope << " and " << o->m_compliance << std::endl;
    }
    else {
        std::cout << "can not find Python3.py  predict_on_data" << std::endl;
    }

    return 0;
}
