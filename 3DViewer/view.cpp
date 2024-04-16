#include "view.h"
#include "./ui_view.h"

using namespace s21;

View::View(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::View)
    , controller(new Controller())
{
    ui->setupUi(this);
}

View::~View()
{
    delete ui;
    delete controller;
}

void View::on_openFile_clicked()
{

}

