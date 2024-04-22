#include "view.h"
#include "./ui_view.h"

using namespace s21;

View::View(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::View)
    , controller(new Controller())
{
    ui->setupUi(this);
    ui->statusbar->addWidget(ui->fileName, 2);
    ui->statusbar->addWidget(ui->numVertices);
    ui->statusbar->addWidget(ui->numEdges);
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
    if (!filename.isEmpty()) {
        ui->fileName->setText("File: " + filename);
        controller->parseFile(filename);
        ui->openGLWidget->setObject(controller->getObject());
        ui->numVertices->setText("Number of vertices: " + QString::number(controller->getObject()->getVerticesQnt()) + ",");
        ui->numEdges->setText("Number of edges: " + QString::number(controller->getObject()->getIndicesQnt() / 3));
    }
}


