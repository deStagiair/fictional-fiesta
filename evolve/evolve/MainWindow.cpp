#include "MainWindow.h"

#include "evolve/ui_MainWindow.h"

#include "fictional-fiesta/utils/itf/Exception.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QObject>

#include <experimental/filesystem>
#include <iostream>

using namespace fictionalfiesta;

namespace fs = std::experimental::filesystem;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  QObject::connect(this, SIGNAL(loadWorld(const QString&)), ui->_worldTab, SLOT(load(const QString&)));
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
      emit loadWorld(q_filename);
    }
    catch (const Exception& e)
    {
      QMessageBox::warning(this, "fictional-fiesta exception", e.what());
    }
  }
}

void MainWindow::on_actionSave_World_as_triggered()
{
  const QString q_filename = QFileDialog::getSaveFileName(this, "Save as",
      "", tr("XML Files (*.xml)"));

  if (!q_filename.isEmpty())
  {
    try
    {
      //_world.save(fs::path(q_filename.toStdString()));
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
