#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "fictional-fiesta/world/itf/World.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionLoad_World_triggered();

    void on_actionQuit_triggered();

private:
    Ui::MainWindow *ui;

    fictionalfiesta::World _world;
};

#endif // MAINWINDOW_H
