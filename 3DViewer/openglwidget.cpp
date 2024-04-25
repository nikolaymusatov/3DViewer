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

void OpenGLWidget::setLinesWidth(int width)
{
    linesWidth = width;
}

void OpenGLWidget::setStippleLines(bool status)
{
    stippleLines = status;
}

void OpenGLWidget::setOrthoProjection(bool status)
{
    orthoProjection = status;
}

void OpenGLWidget::setVerticeColor(QColor color)
{
    vColor = color;
}

void OpenGLWidget::setVerticeSize(int size)
{
    verticeSize = size;
}

void OpenGLWidget::setVerticeType(int type)
{
    verticeType = type;
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
    bgColor = {0.9, 0.9, 0.9};
    pColor = QColor(80, 80, 80, 255);
    vColor = QColor(80, 80, 80, 255);
    linesWidth = 1;
    verticeSize = 1;
    verticeType = 0;
    scale = 1.0;
    stippleLines = false;
    orthoProjection = false;

    initializeOpenGLFunctions();
    glClearColor(bgColor[0], bgColor[1], bgColor[2], 1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    initShaders();

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
    glLineWidth(linesWidth);
    setLinesType();
    setVerticeSettings();
    if (vertices) {
        projectionMatrix.setToIdentity();
        setProjectionType();
        viewMatrix.setToIdentity();
        viewMatrix.lookAt(QVector3D(0, 0, 5), QVector3D(0, 0, 0), QVector3D(0, 1, 0));
        modelMatrix.setToIdentity();
        modelMatrix.scale(scale);
        modelMatrix.rotate(rotation);
        //modelMatrix.translate(translation);
        program.enableAttributeArray("vertexPosition");
        program.setAttributeArray("vertexPosition", vertices->constData());
        program.setUniformValue("renderTexture", false);
        program.setUniformValue("pColor", pColor);
        program.setUniformValue("vColor", vColor);
        program.setUniformValue("modelViewMatrix", viewMatrix * modelMatrix);
        program.setUniformValue("projectionMatrix", projectionMatrix);
        program.setUniformValue("modelViewProjMatrix", projectionMatrix * viewMatrix * modelMatrix);
        glDrawElements(GL_LINES, indices->size(), GL_UNSIGNED_INT, indices->constData());
        if (verticeType) glDrawElements(GL_POINTS, indices->size(), GL_UNSIGNED_INT, indices->constData());
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

void OpenGLWidget::setVerticeSettings()
{
    if (verticeType == 1) {
        glEnable(GL_POINT_SMOOTH);
    } else {
        glDisable(GL_POINT_SMOOTH);
    }
    glPointSize(verticeSize);
}

void OpenGLWidget::setLinesType()
{
    if (stippleLines) {
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(1, 0x00FF);
    } else {
        glDisable(GL_LINE_STIPPLE);
    }
}

void OpenGLWidget::setProjectionType()
{
    if (orthoProjection)
        projectionMatrix.ortho(-2 * aspectRatio, 2 * aspectRatio, -2, 2, 0.001, 10000);
    else
        projectionMatrix.perspective(45, aspectRatio, 0.001f, 1000.0f);
}
