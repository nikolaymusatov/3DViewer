#include "view.h"
#include "./ui_view.h"

using namespace s21;

View::View(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::View)
    , controller(new Controller())
    , settings(new QSettings())
{
    initializeUI();
}

View::~View()
{
    saveSettings();
    delete ui;
}

void View::openFile_clicked()
{
    QString filename = QFileDialog::getOpenFileName(
        this, tr("Open .obj file:"), "~", tr("Obj Files (*.obj)"));
    if (!filename.isEmpty()) {
        ui->fileName->setText("File: " + filename);
        controller->process(filename);
        ui->openGLWidget->setVertices(controller->getVertices());
        ui->openGLWidget->setIndices(controller->getIndices());
        ui->numVertices->setText("Number of vertices: " + QString::number(controller->getVertices()->size()) + ", ");
        ui->numEdges->setText("Number of edges: " + QString::number(controller->getIndices()->size() / 3));
        resetParams_clicked();
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
        ui->openGLWidget->setBackgroundColor(bgColor);
    ui->openGLWidget->update();
}

void View::setPolygonsColor_clicked()
{
    QColor pColor = QColorDialog::getColor();
    if (pColor.isValid())
        ui->openGLWidget->setPolygonsColor(pColor);
    ui->openGLWidget->update();
}

void View::linesWidth_sliderMoved(int position)
{
    ui->openGLWidget->setLinesWidth(position);
    ui->openGLWidget->update();
}

void View::polygonsType_toggled(bool checked)
{
    ui->openGLWidget->setStippleLines(checked);
    ui->openGLWidget->update();
}

void View::setVerticesColor_clicked()
{
    QColor vColor = QColorDialog::getColor();
    if (vColor.isValid())
        ui->openGLWidget->setVerticesColor(vColor);
    ui->openGLWidget->update();
}


void View::sizeVertices_sliderMoved(int position)
{
    ui->openGLWidget->setVerticesSize(position);
    ui->openGLWidget->update();
}

void View::verticesType_toggled()
{
    if(sender()->objectName() == "circleVertice")
        ui->openGLWidget->setVerticesType(1);
    else if(sender()->objectName() == "squareVertice")
        ui->openGLWidget->setVerticesType(2);
    else
        ui->openGLWidget->setVerticesType(0);
    ui->openGLWidget->update();
}


void View::projectionType_toggled(bool checked)
{
    ui->openGLWidget->setOrthoProjection(checked);
    ui->openGLWidget->update();
}

void View::initializeUI()
{
    ui->setupUi(this);
    ui->statusbar->addWidget(ui->fileName, 2);
    ui->statusbar->addWidget(ui->numVertices);
    ui->statusbar->addWidget(ui->numEdges);
    connect(ui->openFile, SIGNAL(clicked()), this, SLOT(openFile_clicked()));
    connect(ui->resetParams, SIGNAL(clicked()), this, SLOT(resetParams_clicked()));
    connect(ui->setBgColor, SIGNAL(clicked()), this, SLOT(setBgColor_clicked()));
    connect(ui->setPolygonColor, SIGNAL(clicked()), this, SLOT(setPolygonsColor_clicked()));
    connect(ui->setVerticeColor, SIGNAL(clicked()), this, SLOT(setVerticesColor_clicked()));
    connect(ui->scale, SIGNAL(valueChanged(double)), this, SLOT(scale_valueChanged()));
    connect(ui->rotateX, SIGNAL(valueChanged(double)), this, SLOT(rotate_valueChanged()));
    connect(ui->rotateY, SIGNAL(valueChanged(double)), this, SLOT(rotate_valueChanged()));
    connect(ui->rotateZ, SIGNAL(valueChanged(double)), this, SLOT(rotate_valueChanged()));
    connect(ui->moveX, SIGNAL(valueChanged(double)), this, SLOT(move_valueChanged()));
    connect(ui->moveY, SIGNAL(valueChanged(double)), this, SLOT(move_valueChanged()));
    connect(ui->moveZ, SIGNAL(valueChanged(double)), this, SLOT(move_valueChanged()));
    connect(ui->linesWidthSlider, SIGNAL(sliderMoved(int)), this, SLOT(linesWidth_sliderMoved(int)));
    connect(ui->dashedPolygonType, SIGNAL(toggled(bool)), this, SLOT(polygonsType_toggled(bool)));
    connect(ui->sizeVerticeSlider, SIGNAL(sliderMoved(int)), this, SLOT(sizeVertices_sliderMoved(int)));
    connect(ui->noneVertice, SIGNAL(toggled(bool)), this, SLOT(verticesType_toggled()));
    connect(ui->circleVertice, SIGNAL(toggled(bool)), this, SLOT(verticesType_toggled()));
    connect(ui->squareVertice, SIGNAL(toggled(bool)), this, SLOT(verticesType_toggled()));
    connect(ui->orthoProjection, SIGNAL(toggled(bool)), this, SLOT(projectionType_toggled(bool)));
    loadSettings();
    setUISettings();
}

void View::saveSettings()
{
    settings->setValue("bgColor", ui->openGLWidget->getBackgroundColor());
    settings->setValue("pColor", ui->openGLWidget->getPolygonsColor());
    settings->setValue("vColor", ui->openGLWidget->getVerticesColor());
    settings->setValue("linesWidth", ui->openGLWidget->getLinesWidth());
    settings->setValue("verticesType", ui->openGLWidget->getVerticesType());
    settings->setValue("verticesSize", ui->openGLWidget->getVerticesSize());
    settings->setValue("orthoProjToggle", ui->openGLWidget->getOrthoProjection());
    settings->setValue("stippleLinesToggle", ui->openGLWidget->getStippleLines());
}

void View::loadSettings()
{
    ui->openGLWidget->setBackgroundColor(settings->value("bgColor", QColor(230, 230, 230, 255)).value<QColor>());
    ui->openGLWidget->setPolygonsColor(settings->value("pColor", QColor(80, 80, 80, 255)).value<QColor>());
    ui->openGLWidget->setVerticesColor(settings->value("vColor", QColor(80, 80, 80, 255)).value<QColor>());
    ui->openGLWidget->setLinesWidth(settings->value("linesWidth", 1).toInt());
    ui->openGLWidget->setVerticesType(settings->value("verticesType", 0).toInt());
    ui->openGLWidget->setVerticesSize(settings->value("verticesSize", 1).toInt());
    ui->openGLWidget->setOrthoProjection(settings->value("orthoProjToggle", false).toBool());
    ui->openGLWidget->setStippleLines(settings->value("stippleLinesToggle", false).toBool());
    ui->openGLWidget->scaleObject(1);
}

void View::setUISettings()
{
    ui->linesWidthSlider->setSliderPosition(ui->openGLWidget->getLinesWidth());
    ui->sizeVerticeSlider->setSliderPosition(ui->openGLWidget->getVerticesSize());
    if (ui->openGLWidget->getStippleLines()) ui->dashedPolygonType->setChecked(true);
    if (ui->openGLWidget->getOrthoProjection()) ui->orthoProjection->setChecked(true);
    if (ui->openGLWidget->getVerticesType() == 1) ui->circleVertice->setChecked(true);
    else if (ui->openGLWidget->getVerticesType() == 1) ui->squareVertice->setChecked(true);
    else ui->noneVertice->setChecked(true);


    // if (ui->widget->edges_type == SOLID) {
    //     ui->solidPolygonType->setChecked(true);
    // } else {
    //     ui->dashedPolygonType->setChecked(true);
    // }
    // if (ui->widget->vertice_type == NONE) {
    //     ui->noneVertice->setChecked(true);
    // } else if (ui->widget->vertice_type == CIRCLE) {
    //     ui->circleVertice->setChecked(true);
    // } else {
    //     ui->squareVertice->setChecked(true);
    // }
    // ui->polygonThickness->setValue(settings->value("edges_thickness").toInt() *
    //                                10);
    // ui->sizeVertice->setValue(settings->value("vertice_size").toInt() * 5);
    // if (ui->widget->projectionType == PARALLEL) {
    //     ui->projectionType->setCurrentIndex(0);
    // } else {
    //     ui->projectionType->setCurrentIndex(1);
    // }
}

