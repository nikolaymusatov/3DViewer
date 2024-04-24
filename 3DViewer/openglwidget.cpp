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

void OpenGLWidget::setBackgroundColor(float red, float green, float blue)
{
    bgColor = {red, green, blue};
    update();
}

void OpenGLWidget::setPolygonColor(QColor color)
{
    pColor = color;
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
    bgColor = {0.9, 0.9, 0.9};
    pColor = QColor(80, 80, 80, 255);
    glClearColor(bgColor[0], bgColor[1], bgColor[2], 1);
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
    glClearColor(bgColor[0], bgColor[1], bgColor[2], 1);
    if (vertices) {
        projectionMatrix.setToIdentity();
        projectionMatrix.perspective(45, aspectRatio, 0.001f, 1000.0f);

        viewMatrix.setToIdentity();
        viewMatrix.lookAt(QVector3D(0, 0, 5), QVector3D(0, 0, 0), QVector3D(0, 1, 0));

        modelMatrix.setToIdentity();
        modelMatrix.scale(scale);
        modelMatrix.rotate(rotation);
        modelMatrix.translate(translation);
        program.enableAttributeArray("vertexPosition");
        program.setAttributeArray("vertexPosition", vertices->constData());
        program.setUniformValue("renderTexture", false);
        program.setUniformValue("pColor", pColor);
        program.setUniformValue("modelViewMatrix", viewMatrix * modelMatrix);
        program.setUniformValue("projectionMatrix", projectionMatrix);
        program.setUniformValue("modelViewProjMatrix", projectionMatrix * viewMatrix * modelMatrix);

        glDrawElements(GL_LINES, indices->size(), GL_UNSIGNED_INT, indices->constData());
    }
}

void OpenGLWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton)
        mousePos = QVector2D(event->position());
    event->accept();
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    float *x, *y, *z;
    if (event->buttons() != Qt::LeftButton) return;
    QVector2D diff = QVector2D(event->position()) - mousePos;
    mousePos = QVector2D(event->position());
    float angle = diff.length() / 2.0;
    QVector3D axis = QVector3D(diff.y(), diff.x(), 0.0f);
    rotation = QQuaternion::fromAxisAndAngle(axis, angle) * rotation;
    update();
}

void OpenGLWidget::initShaders()
{
    program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.vsh");
    program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.fsh");
    program.link();
    program.bind();
}


