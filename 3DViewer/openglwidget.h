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

    void rotateObject(const QVector3D &angles);
    void moveObject(double x, double y, double z);
    void scaleObject(double ratio);

    void setVertices(QVector<QVector3D>* v);
    void setIndices(QVector<GLuint>* i);
    void setBackgroundColor(QColor color);
    void setPolygonsColor(QColor color);
    void setLinesWidth(int width);
    void setStippleLines(bool status);
    void setOrthoProjection(bool status);
    void setVerticesColor(QColor color);
    void setVerticesSize(int size);
    void setVerticesType(int type);

    QColor getBackgroundColor();
    QColor getPolygonsColor();
    QColor getVerticesColor();
    int getLinesWidth();
    int getVerticesSize();
    int getVerticesType();
    bool getStippleLines();
    bool getOrthoProjection();

private:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void wheelEvent(QWheelEvent *) override;
    void initShaders();
    void setVerticesSettings();
    void setLinesType();
    void setProjectionType();

    int linesWidth, verticesSize, verticesType;
    float aspectRatio, scale;
    bool stippleLines;
    bool orthoProjection;
    QColor bgColor, pColor, vColor;
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
