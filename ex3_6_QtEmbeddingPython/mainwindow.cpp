#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "python_interpreter.h"
#include "cspythonhello.h"
void test()
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

}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    test();

}

MainWindow::~MainWindow()
{
    delete ui;
}

