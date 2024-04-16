#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model.h"

namespace s21 {

class Controller {
 public:
    Controller() : model(new Model()) {}
    ~Controller();
  
 private:
  Model *model;
};

}  // namespace s21

#endif  // CONTROLLER_H
