#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model.h"

namespace s21 {

class Controller {
 public:
    Controller() : model(new Model()) {}
    ~Controller();

    void process(QString &path);
    // QVector<QVector3D>* moveModel(GLfloat x, GLfloat y, GLfloat z);
    // QVector<QVector3D>* changeScale(GLfloat ratio);
    QVector<QVector3D>* getVertices();
    QVector<GLuint>* getIndices();
  
 private:
    Model *model;
};

}  // namespace s21

#endif  // CONTROLLER_H
