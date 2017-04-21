#include "structurewindow.h"
#include "ui_structurewindow.h"

StructureWindow::StructureWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StructureWindow)
{
    ui->setupUi(this);
}

StructureWindow::~StructureWindow()
{
    delete ui;
}
