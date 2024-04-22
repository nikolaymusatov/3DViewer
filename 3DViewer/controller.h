#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model.h"

namespace s21 {

class Controller {
 public:
    Controller() : model(new Model()) {}
    ~Controller();

    void parseFile(QString &path);
    Object* getObject();
  
 private:
    Model *model;
};

}  // namespace s21

#endif  // CONTROLLER_H
