#include "controller.h"

using namespace s21;


// Controller::Controller() : model(new Model())
// {
// }

// Controller::~Controller()
// {
//     delete model;
// }

void Controller::process(QString &path)
{
    model->process(path);
}

QVector<QVector3D> *Controller::getVertices()
{
    return model->getVertices();
}

QVector<GLuint> *Controller::getIndices()
{
    return model->getIndices();
}

