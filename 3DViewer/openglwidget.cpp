#include "openglwidget.h"

using namespace s21;

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
    , vertices(nullptr)
    , indices(nullptr)
{
}

void OpenGLWidget::setVertices(QVector<QVector3D> *v)
{
    vertices = v;
}

void OpenGLWidget::setIndices(QVector<GLuint> *i)
{
    indices = i;
}

void OpenGLWidget::initializeGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.9, 0.9, 0.9, 1);
    glColor3f(0.2, 0.2, 0.2);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 1, 10);
    glTranslatef(0, 0, -3);
}

void OpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void OpenGLWidget::paintGL()
{
    glRotatef(xRot, 1, 0, 0);
    glRotatef(yRot, 0, 1, 0);
    if (vertices) {
        glVertexPointer(3, GL_FLOAT, 0, vertices->constData());
        glEnableClientState(GL_VERTEX_ARRAY);
        glDrawElements(GL_LINES, indices->size(), GL_UNSIGNED_INT, indices->constData());
        glDisableClientState(GL_VERTEX_ARRAY);
    }
}

void OpenGLWidget::mousePressEvent(QMouseEvent *mouse)
{
    mousePos = mouse->pos();
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent *mouse)
{
    xRot = 0.01 / M_PI * (mouse->pos().y() - mousePos.y());
    yRot = 0.01 / M_PI * (mouse->pos().x() - mousePos.x());
    update();
}

