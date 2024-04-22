#ifndef OBJECT_H
#define OBJECT_H

#include <QOpenGLWidget>

class Object
{
public:
    Object() = default;

    void clear();
    void addVertice(GLfloat vertice);
    void addIndex(GLuint index);
    QVector<GLfloat>* getVertices();
    QVector<GLuint>* getIndices();
    size_t getVerticesQnt();
    size_t getIndicesQnt();

private:
    QVector<GLfloat> vertices;
    QVector<GLuint> indices;
};

#endif // OBJECT_H
