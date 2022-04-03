#ifndef SCENE_H
#define SCENE_H

// Project
#include "deck.h"

// Qt
#include <QGraphicsItem>
#include <QGraphicsScene>


class Scene : public QGraphicsScene
{
public:
  Scene();

  void refresh();

  Deck d;
};


#endif // SCENE_H
