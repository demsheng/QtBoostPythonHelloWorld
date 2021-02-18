
#define BOOST_BIND_GLOBAL_PLACEHOLDERS

//它可以让VC在编译时的output窗口中输出程序具体链接了哪些boost库以及链接顺序。
#define BOOST_LIB_DIAGNOSTIC

//告诉boost禁用自动链接。
#define BOOST_ALL_NO_LIB

#define BOOST_PYTHON_STATIC_LIB

//test_class_wrapper.cpp
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
        .def("cs", &A::cs)                            //成员函数
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
