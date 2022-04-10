#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "savefile.h"
#include "scene.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void connectImageButtons();
    void connectCardGroup();
    void connectMainGroup();
    void connectMinorGroup();

    SaveFile saveFile;
    Ui::MainWindow *ui = nullptr;
    Scene *scene = nullptr;
};
#endif // MAINWINDOW_H
