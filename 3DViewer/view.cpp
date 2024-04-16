#include "view.h"
#include "./ui_view.h"

using namespace s21;

View::View(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::View)
    , controller(new Controller())
{
    ui->setupUi(this);
    connect(ui->openFile, SIGNAL(clicked()), this, SLOT(openFile_clicked()));
}

View::~View()
{
    delete ui;
    delete controller;
}

void View::openFile_clicked()
{
    QString filename = QFileDialog::getOpenFileName(
        this, tr("Open .obj file:"), "~", tr("Obj Files (*.obj)"));
    ui->filePath->setText(filename);
    // ui->openGLWidget->fileChanged = true;
}

