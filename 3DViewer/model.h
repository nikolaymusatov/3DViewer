#ifndef MODEL_H
#define MODEL_H

#include <QFile>
#include <QTextStream>
#include <QVector3D>
#include <QOpenGLWidget>


namespace s21 {

class Model {
 public:
    Model() = default;
     ~Model() {}

    void parseFile(QString& path);
    QVector<QVector3D>* getVertices();
    QVector<GLuint>* getIndices();

 private:
    QVector<QVector3D> vertices;
    QVector<GLuint> indices;

    void parseVertice(QStringList &line);
    void parseFace(QStringList &line);
    void centerModel();
};

}  // namespace s21

#endif  // MODEL_H
