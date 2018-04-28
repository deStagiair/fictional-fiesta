#ifndef WORLDVIEW_H
#define WORLDVIEW_H

#include <QWidget>

#include "fictional-fiesta/world/itf/FSM.h"
#include "fictional-fiesta/world/itf/World.h"

namespace Ui
{
class WorldView;
}

class WorldView : public QWidget
{
  Q_OBJECT

  public:
      explicit WorldView(QWidget *parent = 0);
      ~WorldView();

  public slots:

    void load(const QString& filename);
    void worldChanged();

    void simulate();

    void setRngSeed(unsigned int seed);

  private:

    Ui::WorldView *ui;

    fictionalfiesta::FSM::Rng _rng;
    fictionalfiesta::World _world;
};

#endif // WORLDVIEW_H
