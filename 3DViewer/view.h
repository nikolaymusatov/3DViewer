#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <QFileDialog>
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
    void applyParams_clicked();
    void resetParams_clicked();
    void scale_valueChanged(double ratio);

private:
    Ui::View *ui;
    Controller *controller;

};

}  // namespace s21

#endif // VIEW_H
