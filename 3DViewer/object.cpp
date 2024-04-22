#include "object.h"

void Object::clear()
{
    vertices.clear();
    indices.clear();
}

void Object::addVertice(GLfloat vertice)
{
    vertices.append(vertice);
}

void Object::addIndex(GLuint index)
{
    indices.append(index);
}

QVector<GLfloat> *Object::getVertices()
{
    return &vertices;
}

QVector<GLuint> *Object::getIndices()
{
    return &indices;
}

size_t Object::getVerticesQnt()
{
    return vertices.size();
}

size_t Object::getIndicesQnt()
{
    return indices.size();
}
