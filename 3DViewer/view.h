#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QColorDialog>
#include <QSettings>
#include <memory>
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
    void setPolygonsColor_clicked();
    void setVerticesColor_clicked();
    void scale_valueChanged();
    void rotate_valueChanged();
    void move_valueChanged();
    void linesWidth_sliderMoved(int position);
    void sizeVertices_sliderMoved(int position);
    void polygonsType_toggled(bool checked);
    void verticesType_toggled();
    void projectionType_toggled(bool checked);

private:
    Ui::View *ui;
    std::unique_ptr<Controller> controller;
    std::unique_ptr<QSettings> settings;

    void initializeUI();
    void saveSettings();
    void loadSettings();
    void setUISettings();
};

}  // namespace s21

#endif // VIEW_H
