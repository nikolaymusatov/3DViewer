#include "controller.h"

using namespace s21;


Controller::~Controller()
{
    delete model;
}

void Controller::process(QString &path)
{
    model->process(path);
}

// QVector<QVector3D> *Controller::moveModel(GLfloat x, GLfloat y, GLfloat z)
// {
//     return model->moveModel(x, y, z);
// }

// QVector<QVector3D>* Controller::changeScale(GLfloat ratio)
// {
//     return model->changeScale(ratio);
// }

QVector<QVector3D> *Controller::getVertices()
{
    return model->getVertices();
}

QVector<GLuint> *Controller::getIndices()
{
    return model->getIndices();
}

