#include "openglwidget.h"
#include <QDebug>
#include <iostream>

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

void OpenGLWidget::rotateObject(const QVector3D &angles)
{
    rotation = QQuaternion::fromEulerAngles(angles);
}

void OpenGLWidget::moveObject(double x, double y, double z)
{
    translation.setX(x);
    translation.setY(y);
    translation.setZ(z - 5);
}

void OpenGLWidget::scaleObject(double ratio)
{
    scale = ratio;
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.9, 0.9, 0.9, 1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    initShaders();
    scale = 1.0;
}

void OpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    aspectRatio = w / (h ? (float)h : 1);
}

void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (vertices) {
        projectionMatrix.setToIdentity();
        projectionMatrix.perspective(45, aspectRatio, 0.001f, 1000.0f);

        viewMatrix.setToIdentity();
        viewMatrix.lookAt(QVector3D(0, 0, 5), QVector3D(0, 0, 0), QVector3D(0, 1, 0));

        modelMatrix.setToIdentity();
        modelMatrix.scale(scale);
        modelMatrix.rotate(rotation);
        modelMatrix.translate(translation);

        // for (int i = 0; i < 4; i++) {
        //     for (int j = 0; j < 4; j++)
        //         std::cout << (viewMatrix * modelMatrix)(i, j) << "    ";
        //     std::cout << std::endl;
        // }

        program.enableAttributeArray("vertexPosition");
        program.setAttributeArray("vertexPosition", vertices->constData());
        program.setUniformValue("renderTexture", false);

        program.setUniformValue("modelViewMatrix", viewMatrix * modelMatrix);
        program.setUniformValue("projectionMatrix", projectionMatrix);
        program.setUniformValue("modelViewProjMatrix", projectionMatrix * viewMatrix * modelMatrix);

        glDrawElements(GL_LINES, indices->size(), GL_UNSIGNED_INT, indices->constData());
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

void OpenGLWidget::initShaders()
{
    program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.vsh");
    program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.fsh");
    program.link();
    program.bind();
}


