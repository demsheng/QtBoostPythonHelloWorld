#define BOOST_BIND_GLOBAL_PLACEHOLDERS

#define BOOST_LIB_DIAGNOSTIC
//它可以让VC在编译时的output窗口中输出程序具体链接了哪些boost库以及链接顺序。

#define BOOST_ALL_NO_LIB
//告诉boost禁用自动链接。

#include <iostream>
#include <Python.h>
#include <boost/python.hpp>
#include <iostream>
#include <string>
#include <string.h>
#include <fstream>

using namespace std;
using namespace boost::python;

int main() {
    //初始化读取 py 文件的信息
    std::ifstream fin;
    fin.open("../ex2_cppEmbeddingPythonInterpreter/script.py");
    std::string str;
    std::string str_in = "";
    while (getline(fin, str))    //一行一行地读到字符串str_in中
    {
        str_in = str_in + str + '\n';
    }
    fin.close();
    cout<<str_in<<endl;
    Py_Initialize();
//    PyRun_SimpleString("from time import time,ctime\n"
//    "print 'Today is',ctime(time())\n");
    PyRun_SimpleString(str_in.c_str());
    Py_Finalize();
    cout<<"it is over ...."<<endl;
    return 0;
}
