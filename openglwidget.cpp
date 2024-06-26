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

QColor OpenGLWidget::getBackgroundColor() const
{
    return bgColor;
}

QColor OpenGLWidget::getPolygonsColor() const
{
    return pColor;
}

QColor OpenGLWidget::getVerticesColor() const
{
    return vColor;
}

int OpenGLWidget::getLinesWidth() const
{
    return linesWidth;
}

int OpenGLWidget::getVerticesSize() const
{
    return verticesSize;
}

int OpenGLWidget::getVerticesType() const
{
    return verticesType;
}

bool OpenGLWidget::getStippleLines() const
{
    return stippleLines;
}

bool OpenGLWidget::getOrthoProjection() const
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
    translation.setZ(z);
}

void OpenGLWidget::scaleObject(double ratio)
{
    scale = ratio;
}

void OpenGLWidget::initializeGL()
{
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
    glClearColor(bgColor.redF(), bgColor.greenF(), bgColor.blueF(), bgColor.alphaF());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLineWidth(linesWidth);
    setLinesType();
    setVerticesSettings();
    if (vertices) {
        mvpMatrix.setToIdentity();
        setProjectionType();
        mvpMatrix.lookAt(QVector3D(0, 0, 5), QVector3D(0, 0, 0), QVector3D(0, 1, 0));
        mvpMatrix.scale(scale);
        mvpMatrix.rotate(rotation);
        mvpMatrix.translate(translation);
        program.enableAttributeArray("vertexPosition");
        program.setAttributeArray("vertexPosition", vertices->constData());
        program.setUniformValue("color", pColor);
        program.setUniformValue("mvpMatrix", mvpMatrix);
        glDrawElements(GL_LINES, indices->size(), GL_UNSIGNED_INT, indices->constData());
        if (verticesType) {
            program.setUniformValue("color", vColor);
            glDrawElements(GL_POINTS, indices->size(), GL_UNSIGNED_INT, indices->constData());
        }

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
        mvpMatrix.ortho(-1.7 * aspectRatio, 1.7 * aspectRatio, -1.7, 1.7, 0.001, 10000);
    else
        mvpMatrix.perspective(45, aspectRatio, 0.001f, 1000.0f);
}
