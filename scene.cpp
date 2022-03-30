#include "scene.h"
#include "cardinfo.h"

constexpr int buffer = 50;
Scene::Scene()
{
    setSceneRect(0,0,700,10000);
}

void Scene::load(const QString &)
{
    //TODO
}

void Scene::refresh()
{
    static int x = 0;
    static int y = 0;
    QSize cardDimensions = d.context.cardSize();
    for(auto card : d.cards)
    {
       static int x = 0;
       auto item = card->generateGraphicsItem(d.context, this);
       item->moveBy(x + buffer, y + buffer);
       x += cardDimensions.width();
       if(x > sceneRect().width())
       {
           x = 0;
           y += cardDimensions.height() + buffer;
       }
    }

  for(int i = 0; i < 9; i++)
  {
      auto item = CardInfo::generateCardBackGraphicsItem(d.context, this);
      item->moveBy(x + buffer, y + buffer);
      x += cardDimensions.width();
      if(x > sceneRect().width())
      {
          x = 0;
          y += cardDimensions.height() + buffer;
      }
  }
}
