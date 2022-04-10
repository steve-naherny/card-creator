#include "scene.h"
#include "cardinfo.h"

constexpr int buffer = 25;
constexpr int numberOfCardsPerLine = 4;
Scene::Scene()
{
    Context &c = d.context;
    QSize cardDimensions = c.cardSize();
    c.cardBack.background.size = cardDimensions;
    c.cardBack.foreground.size = c.cardBack.foreGroundSize();
    c.mainCharacter.regularPortrait.size = cardDimensions;
    c.mainCharacter.specialPortrait.size = cardDimensions;
    c.minorCharacter.regularPortrait.size = cardDimensions;
    c.minorCharacter.specialPortrait.size = cardDimensions;
    c.special.frame.size = cardDimensions;
    c.unique.frame.size = cardDimensions;
    c.unique.defenseFrame.size = c.unique.frameSize();
    c.unique.attackFrame.size = c.unique.frameSize();
    c.combat.frame.size = c.combat.frameSize();
}

void Scene::clear()
{
    d.cards.clear();
    QGraphicsScene::clear();
}

void Scene::refresh()
{
    QGraphicsScene::clear();
    setSceneRect(QRectF());
    int x = 0;
    int y = 0;
    QSize cardDimensions = d.context.cardSize();
    for(auto card : d.cards)
    {
        static int x = 0;
        auto item = card->generateGraphicsItem(d.context, this);
        item->moveBy(x + buffer, y + buffer);
        x += cardDimensions.width();
        int currentX = x + cardDimensions.width();
        int pageWidth  = numberOfCardsPerLine * cardDimensions.width();
        if(currentX > pageWidth)
        {
            x = 0;
            y += cardDimensions.height() + buffer;
        }
    }

//    for(int i = 0; i < 9; i++)
//    {
//        auto item = CardInfo::generateCardBackGraphicsItem(d.context, this);
//        item->moveBy(x + buffer, y + buffer);
//        x += cardDimensions.width();
//        int currentX = x + cardDimensions.width();
//        int pageWidth  = numberOfCardsPerLine * cardDimensions.width();
//        if(currentX > pageWidth)
//        {
//            x = 0;
//            y += cardDimensions.height() + buffer;
//        }
//    }
}
