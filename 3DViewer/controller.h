#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>
#include "model.h"

namespace s21 {

class Controller {
 public:
    Controller() : model(new Model()) {}
    ~Controller() {}

    void process(QString &path);
    QVector<QVector3D>* getVertices();
    QVector<GLuint>* getIndices();
  
 private:
    std::unique_ptr<Model> model;
};

}  // namespace s21

#endif  // CONTROLLER_H
