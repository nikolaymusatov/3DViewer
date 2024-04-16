#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QWidget>
#include <iostream>

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
public:
    explicit OpenGLWidget(QWidget *parent = Q_NULLPTR);
    double bg_red = 0, bg_green = 0, bg_blue = 0;
    double pol_red = 0, pol_green = 0, pol_blue = 0;
    double ver_red = 0, ver_green = 0, ver_blue = 0;
    double edges_thickness = 1, vertice_size = 1;
    int vertice_type = 0, projectionType = 0, edges_type = 0;

private:
    ~OpenGLWidget() override;
    QPointF lastMousePos;
;

protected:
    // OPENGL

};

#endif // OPENGLWIDGET_H
