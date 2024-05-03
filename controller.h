#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>
#include "model.h"

namespace s21 {

class Controller {
 public:
    static Controller* Instance();

    void process(QString &path);
    QVector<QVector3D>* getVertices();
    QVector<GLuint>* getIndices();
  
 private:
    Controller() : model(Model::Instance()) {}
    Controller(const Controller &) = delete;
    Controller& operator=(const Controller &) = delete;

    Model* model;
};

}  // namespace s21

#endif  // CONTROLLER_H
