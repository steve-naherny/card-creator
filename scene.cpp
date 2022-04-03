#include "scene.h"
#include "cardinfo.h"

constexpr int buffer = 25;
Scene::Scene()
{
    setBackgroundBrush(QBrush(QColor("#fffdd0")));
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
       if(x + cardDimensions.width() > 5 * cardDimensions.width())
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
      if(x + cardDimensions.width() > 5 * cardDimensions.width())
      {
          x = 0;
          y += cardDimensions.height() + buffer;
      }
  }
}
