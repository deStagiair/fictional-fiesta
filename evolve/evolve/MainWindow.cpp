#include "MainWindow.h"

#include "evolve/ui_MainWindow.h"

#include "fictional-fiesta/utils/itf/Exception.h"

#include <QFileDialog>
#include <QMessageBox>

#include <experimental/filesystem>
#include <iostream>

using namespace fictionalfiesta;

namespace fs = std::experimental::filesystem;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionLoad_World_triggered()
{
  const QString q_filename = QFileDialog::getOpenFileName(this, "Open the World file",
      "", tr("XML Files (*.xml)"));

  if (!q_filename.isEmpty())
  {
    try
    {
      _world = World(fs::path(q_filename.toStdString()));
    }
    catch (const Exception& e)
    {
      QMessageBox::warning(this, "fictional-fiesta exception", e.what());
    }
  }
}

void MainWindow::on_actionQuit_triggered()
{
  QCoreApplication::quit();
}
