#include "WorldView.h"
#include "ui_WorldView.h"

using namespace fictionalfiesta;

WorldView::WorldView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WorldView)
{
    ui->setupUi(this);
    QObject::connect(ui->evolvePushButton, SIGNAL(clicked()), this, SLOT(simulate()));
    QObject::connect(ui->resetPushButton, SIGNAL(clicked()), this, SLOT(reset()));
}

WorldView::~WorldView()
{
    delete ui;
}

void WorldView::load(const QString& filename)
{
  const std::experimental::filesystem::path path(filename.toStdString());
  _world = World{path};
  _initialWorld = _world;

  worldChanged();
}

void WorldView::reset()
{
  _world = _initialWorld;

  worldChanged();
}

void WorldView::worldChanged()
{
  ui->_xmlText->setText(QString(_world.saveXmlToString().c_str()));
}

void WorldView::simulate()
{
  const auto cycle_count = ui->cyclesSpinBox->value();

  for (auto cycle_index = 0; cycle_index < cycle_count; ++cycle_index)
  {
    _world.cycle(_rng);
  }

  worldChanged();
}

void WorldView::setRngSeed(unsigned int seed)
{
}
