#ifndef MODEL_H
#define MODEL_H

#include <QFile>
#include <QTextStream>
#include <QOpenGLWidget>
#include "object.h"


namespace s21 {

class Model {
 public:
    Model() = default;
     ~Model() {}

    void parseFile(QString& path);
    Object* getObject();

 private:
    Object object;

    void parseVertice(QStringList &line);
    void parseFace(QStringList &line);
};

}  // namespace s21

#endif  // MODEL_H
