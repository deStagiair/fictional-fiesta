#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    void on_actionSave_World_as_triggered();

    void on_actionQuit_triggered();

signals:

    void loadWorld(const QString& path);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
