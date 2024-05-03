#include "controller.h"

using namespace s21;


Controller *Controller::Instance()
{
    static Controller controller;
    return &controller;
}

void Controller::process(QString &path)
{
    model->Instance()->parseFile(path);
}

QVector<QVector3D> *Controller::getVertices()
{
    return model->Instance()->getVertices();
}

QVector<GLuint> *Controller::getIndices()
{
    return model->Instance()->getIndices();
}

