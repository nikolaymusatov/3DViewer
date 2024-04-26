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

void OpenGLWidget::setBackgroundColor(QColor color)
{
    bgColor = color;
    update();
}

void OpenGLWidget::setPolygonsColor(QColor color)
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

void OpenGLWidget::setVerticesColor(QColor color)
{
    vColor = color;
}

void OpenGLWidget::setVerticesSize(int size)
{
    verticesSize = size;
}

void OpenGLWidget::setVerticesType(int type)
{
    verticesType = type;
}

QColor OpenGLWidget::getBackgroundColor()
{
    return bgColor;
}

QColor OpenGLWidget::getPolygonsColor()
{
    return pColor;
}

QColor OpenGLWidget::getVerticesColor()
{
    return vColor;
}

int OpenGLWidget::getLinesWidth()
{
    return linesWidth;
}

int OpenGLWidget::getVerticesSize()
{
    return verticesSize;
}

int OpenGLWidget::getVerticesType()
{
    return verticesType;
}

bool OpenGLWidget::getStippleLines()
{
    return stippleLines;
}

bool OpenGLWidget::getOrthoProjection()
{
    return orthoProjection;
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
    // bgColor = QColor(230, 230, 230, 255);
    // pColor = QColor(80, 80, 80, 255);
    // vColor = QColor(80, 80, 80, 255);
    // linesWidth = 1;
    // verticesSize = 1;
    // verticesType = 0;
    // scale = 1.0;
    // stippleLines = false;
    // orthoProjection = false;

    initializeOpenGLFunctions();
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
    glClearColor(bgColor.redF(), bgColor.greenF(), bgColor.blueF(), bgColor.alphaF());
    glLineWidth(linesWidth);
    setLinesType();
    setVerticesSettings();
    if (vertices) {
        projectionMatrix.setToIdentity();
        setProjectionType();
        viewMatrix.setToIdentity();
        viewMatrix.lookAt(QVector3D(0, 0, 5), QVector3D(0, 0, 0), QVector3D(0, 1, 0));
        modelMatrix.setToIdentity();
        modelMatrix.scale(scale);
        modelMatrix.rotate(rotation);
        modelMatrix.translate(translation); // ошибка проекции
        program.enableAttributeArray("vertexPosition");
        program.setAttributeArray("vertexPosition", vertices->constData());
        program.setUniformValue("renderTexture", false);
        program.setUniformValue("pColor", pColor);
        program.setUniformValue("vColor", vColor);
        program.setUniformValue("modelViewMatrix", viewMatrix * modelMatrix);
        program.setUniformValue("projectionMatrix", projectionMatrix);
        program.setUniformValue("modelViewProjMatrix", projectionMatrix * viewMatrix * modelMatrix);
        glDrawElements(GL_LINES, indices->size(), GL_UNSIGNED_INT, indices->constData());
        if (verticesType) glDrawElements(GL_POINTS, indices->size(), GL_UNSIGNED_INT, indices->constData());
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

void OpenGLWidget::wheelEvent(QWheelEvent *event)
{
    QPoint angleDelta = event->angleDelta();
    if (!angleDelta.isNull()) {
        int delta = angleDelta.y();
        if (delta > 0)
            scale *= 1.02;
        else
            scale /= 1.02;

        update();
    }
}

void OpenGLWidget::initShaders()
{
    program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.vsh");
    program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.fsh");
    program.link();
    program.bind();
}

void OpenGLWidget::setVerticesSettings()
{
    if (verticesType == 1) {
        glEnable(GL_POINT_SMOOTH);
    } else {
        glDisable(GL_POINT_SMOOTH);
    }
    glPointSize(verticesSize);
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
        projectionMatrix.ortho(-1.7 * aspectRatio, 1.7 * aspectRatio, -1.7, 1.7, 0.001, 10000);
    else
        projectionMatrix.perspective(45, aspectRatio, 0.001f, 1000.0f);
}
