#include "openglwidget.h"

using namespace s21;

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
    , object(nullptr)
{
}

void OpenGLWidget::setObject(Object *obj)
{
    object = obj;
}

void OpenGLWidget::initializeGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.9, 0.9, 0.9, 1);
    glEnable(GL_DEPTH_TEST);
}

void OpenGLWidget::resizeGL(int w, int h)
{

}

void OpenGLWidget::paintGL()
{
    if (object->getVertices()) {
        glVertexPointer(3, GL_FLOAT, 0, object->getVertices()->constData());
        glEnableClientState(GL_VERTEX_ARRAY);
        glDrawElements(GL_TRIANGLES, object->getIndicesQnt(), GL_UNSIGNED_INT, object->getIndices()->constData());
        glDisableClientState(GL_VERTEX_ARRAY);
    }
}

