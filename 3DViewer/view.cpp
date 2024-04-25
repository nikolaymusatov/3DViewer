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
    connect(ui->setBgColor, SIGNAL(clicked()), this, SLOT(setBgColor_clicked()));
    connect(ui->setPolygonColor, SIGNAL(clicked()), this, SLOT(setPolygonColor_clicked()));
    connect(ui->setVerticeColor, SIGNAL(clicked()), this, SLOT(setVerticeColor_clicked()));
    connect(ui->scale, SIGNAL(valueChanged(double)), this, SLOT(scale_valueChanged()));
    connect(ui->rotateX, SIGNAL(valueChanged(double)), this, SLOT(rotate_valueChanged()));
    connect(ui->rotateY, SIGNAL(valueChanged(double)), this, SLOT(rotate_valueChanged()));
    connect(ui->rotateZ, SIGNAL(valueChanged(double)), this, SLOT(rotate_valueChanged()));
    connect(ui->moveX, SIGNAL(valueChanged(double)), this, SLOT(move_valueChanged()));
    connect(ui->moveY, SIGNAL(valueChanged(double)), this, SLOT(move_valueChanged()));
    connect(ui->moveZ, SIGNAL(valueChanged(double)), this, SLOT(move_valueChanged()));
    connect(ui->linesWidth, SIGNAL(sliderMoved(int)), this, SLOT(linesWidth_sliderMoved(int)));
    connect(ui->dashedPolygonType, SIGNAL(toggled(bool)), this, SLOT(polygonType_toggled(bool)));
    connect(ui->sizeVertice, SIGNAL(sliderMoved(int)), this, SLOT(sizeVertice_sliderMoved(int)));
    connect(ui->noneVertice, SIGNAL(toggled(bool)), this, SLOT(verticeType_toggled()));
    connect(ui->circleVertice, SIGNAL(toggled(bool)), this, SLOT(verticeType_toggled()));
    connect(ui->squareVertice, SIGNAL(toggled(bool)), this, SLOT(verticeType_toggled()));
    connect(ui->orthoProjection, SIGNAL(toggled(bool)), this, SLOT(projectionType_toggled(bool)));
}

View::~View()
{
    delete ui;
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

void View::setBgColor_clicked()
{
    QColor bgColor = QColorDialog::getColor();
    if (bgColor.isValid())
        ui->openGLWidget->setBackgroundColor(bgColor.redF(), bgColor.greenF(), bgColor.blueF());
    ui->openGLWidget->update();
}

void View::setPolygonColor_clicked()
{
    QColor pColor = QColorDialog::getColor();
    if (pColor.isValid())
        ui->openGLWidget->setPolygonColor(pColor);
    ui->openGLWidget->update();
}

void View::linesWidth_sliderMoved(int position)
{
    ui->openGLWidget->setLinesWidth(position);
    ui->openGLWidget->update();
}

void View::polygonType_toggled(bool checked)
{
    ui->openGLWidget->setStippleLines(checked);
    ui->openGLWidget->update();
}

void View::setVerticeColor_clicked()
{
    QColor vColor = QColorDialog::getColor();
    if (vColor.isValid())
        ui->openGLWidget->setVerticeColor(vColor);
    ui->openGLWidget->update();
}


void View::sizeVertice_sliderMoved(int position)
{
    ui->openGLWidget->setVerticeSize(position);
    ui->openGLWidget->update();
}

void View::verticeType_toggled()
{
    if(sender()->objectName() == "circleVertice")
        ui->openGLWidget->setVerticeType(1);
    else if(sender()->objectName() == "squareVertice")
        ui->openGLWidget->setVerticeType(2);
    else
        ui->openGLWidget->setVerticeType(0);
    ui->openGLWidget->update();
}


void View::projectionType_toggled(bool checked)
{
    ui->openGLWidget->setOrthoProjection(checked);
    ui->openGLWidget->update();
}

