#include "controller.h"

using namespace s21;


Controller::~Controller()
{
    delete model;
}

void Controller::parseFile(QString &path)
{
    model->parseFile(path);
}

Object *Controller::getObject()
{
    return model->getObject();
}

