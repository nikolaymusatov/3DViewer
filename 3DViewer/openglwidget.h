#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QColor>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QVector3D>
#include <QMouseEvent>

namespace s21 {

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = 0);
    ~OpenGLWidget() {}

    void setVertices(QVector<QVector3D>* v);
    void setIndices(QVector<GLuint>* i);
    void setBackgroundColor(float red, float green, float blue);
    void setPolygonColor(QColor color);
    void rotateObject(const QVector3D &angles);
    void moveObject(double x, double y, double z);
    void scaleObject(double ratio);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void initShaders();
    void initObject();

private:
    float aspectRatio, scale;
    QVector<GLfloat> bgColor;
    QColor pColor;
    QVector2D mousePos;
    QQuaternion rotation;
    QVector3D translation;
    QMatrix4x4 modelMatrix, viewMatrix, projectionMatrix;
    QVector<QVector3D>* vertices;
    QVector<GLuint>* indices;
    QOpenGLShaderProgram program;
};

}

#endif // OPENGLWIDGET_H
