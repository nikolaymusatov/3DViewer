#include "controller.h"

using namespace s21;


void Controller::process(QString &path)
{
    model->parseFile(path);
}

QVector<QVector3D> *Controller::getVertices()
{
    return model->getVertices();
}

QVector<GLuint> *Controller::getIndices()
{
    return model->getIndices();
}

