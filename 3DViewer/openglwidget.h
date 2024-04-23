#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QVector3D>
#include <QMouseEvent>

namespace s21 {

class OpenGLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = 0);
    ~OpenGLWidget() {}

    void setVertices(QVector<QVector3D>* v);
    void setIndices(QVector<GLuint>* i);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;

private:
    float xRot, yRot;
    QPoint mousePos;
    QVector<QVector3D>* vertices;
    QVector<GLuint>* indices;
};

}

#endif // OPENGLWIDGET_H
