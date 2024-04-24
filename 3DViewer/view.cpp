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
    connect(ui->resetParams, SIGNAL(clicked()), this, SLOT(resetParams_clicked()));
    connect(ui->scale, SIGNAL(valueChanged(double)), this, SLOT(scale_valueChanged()));
    connect(ui->rotateX, SIGNAL(valueChanged(double)), this, SLOT(rotate_valueChanged()));
    connect(ui->rotateY, SIGNAL(valueChanged(double)), this, SLOT(rotate_valueChanged()));
    connect(ui->rotateZ, SIGNAL(valueChanged(double)), this, SLOT(rotate_valueChanged()));
    connect(ui->moveX, SIGNAL(valueChanged(double)), this, SLOT(move_valueChanged()));
    connect(ui->moveY, SIGNAL(valueChanged(double)), this, SLOT(move_valueChanged()));
    connect(ui->moveZ, SIGNAL(valueChanged(double)), this, SLOT(move_valueChanged()));
}

View::~View()
{
    delete ui;
    //delete controller;
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

void View::resetParams_clicked()
{
    ui->scale->setValue(1);
    ui->rotateX->setValue(0);
    ui->rotateY->setValue(0);
    ui->rotateZ->setValue(0);
    ui->moveX->setValue(0);
    ui->moveY->setValue(0);
    ui->moveZ->setValue(0);
    ui->openGLWidget->update();
}

void View::scale_valueChanged()
{
    ui->openGLWidget->scaleObject(ui->scale->value());
    ui->openGLWidget->update();
}

void View::rotate_valueChanged()
{
    ui->openGLWidget->rotateObject(QVector3D(ui->rotateX->value(), ui->rotateY->value(), ui->rotateZ->value()));
    ui->openGLWidget->update();
}

void View::move_valueChanged()
{
    ui->openGLWidget->moveObject(ui->moveX->value(), ui->moveY->value(), ui->moveZ->value());
    ui->openGLWidget->update();
}
