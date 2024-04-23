#include "view.h"
#include "./ui_view.h"
#include <iostream>

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
    connect(ui->resetParams, SIGNAL(clicked()), this, SLOT(resetParams_clicked()));
    connect(ui->scale, SIGNAL(valueChanged(double)), this, SLOT(scale_valueChanged(double)));
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
        controller->process(filename);
        ui->scale->setValue(1);
        ui->openGLWidget->setVertices(controller->getVertices());
        ui->openGLWidget->setIndices(controller->getIndices());
        ui->numVertices->setText("Number of vertices: " + QString::number(controller->getVertices()->size()) + ", ");
        ui->numEdges->setText("Number of edges: " + QString::number(controller->getIndices()->size() / 3));
    }
}

void View::applyParams_clicked()
{
    float xOffset = ui->move_on_x->value();
    float yOffset = ui->move_on_x->value();
    float zOffset = ui->move_on_x->value();
    ui->openGLWidget->setVertices(controller->moveModel(xOffset, yOffset, zOffset));
    ui->openGLWidget->update();
}


void View::resetParams_clicked()
{
    ui->scale->setValue(1);
    ui->openGLWidget->setVertices(controller->getVertices());
    ui->openGLWidget->update();
}


void View::scale_valueChanged(double ratio)
{
    ui->openGLWidget->setVertices(controller->changeScale((GLfloat)ratio));
    ui->openGLWidget->update();
}

