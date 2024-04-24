#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QColorDialog>
#include <memory>
#include "openglwidget.h"
#include "controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

namespace s21 {

class View : public QMainWindow
{
    Q_OBJECT

public:
    View(QWidget *parent = nullptr);
    ~View();

private slots:
    void openFile_clicked();
    void resetParams_clicked();
    void setBgColor_clicked();
    void setPolygonColor_clicked();
    void scale_valueChanged();
    void rotate_valueChanged();
    void move_valueChanged();

private:
    Ui::View *ui;
    std::unique_ptr<Controller> controller;

};

}  // namespace s21

#endif // VIEW_H
