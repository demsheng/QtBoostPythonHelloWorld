#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "python_interpreter.h"

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

