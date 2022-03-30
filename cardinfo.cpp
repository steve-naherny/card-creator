#include "cardinfo.h"

// Qt
#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QGraphicsScene>

QGraphicsItemGroup *SuperCard::generateGraphicsItem(Context &context, QGraphicsScene *scene)
{
    QGraphicsItemGroup *group = new QGraphicsItemGroup;
    QGraphicsPixmapItem *background = new QGraphicsPixmapItem(group);
    background->setPixmap(context.mainCharacter.regularPortrait);

    QGraphicsPixmapItem *combat = new QGraphicsPixmapItem(group);
    combat->setPixmap(context.combat.frame);

    QGraphicsTextItem * attackItem = new QGraphicsTextItem(group);
    attackItem->setPlainText(QString::number(attack));

    QGraphicsTextItem *defenseItem = new QGraphicsTextItem(group);
    defenseItem->setPlainText(QString::number(defense));
    return group;
}

QGraphicsItemGroup *SpecialCard::generateGraphicsItem(Context &context, QGraphicsScene *scene)
{
    QGraphicsItemGroup *group = new QGraphicsItemGroup;
    QGraphicsPixmapItem *background = new QGraphicsPixmapItem(group);
    background->setPixmap(context.mainCharacter.regularPortrait);

    QGraphicsPixmapItem *combat = new QGraphicsPixmapItem(group);
    combat->setPixmap(context.combat.frame);

    QGraphicsTextItem * attackItem = new QGraphicsTextItem(group);
    attackItem->setPlainText(QString::number(attack));

    QGraphicsTextItem *defenseItem = new QGraphicsTextItem(group);
    defenseItem->setPlainText(QString::number(defense));
    return group;
}

QGraphicsItemGroup* MinorCombatCard::generateGraphicsItem(Context &context, QGraphicsScene *scene)
{
    return generateCombatCard(context.minorCharacter, context.combat, scene);
}

QGraphicsItemGroup* CombatCard::generateGraphicsItem(Context &context, QGraphicsScene *scene)
{
    return generateCombatCard(context.mainCharacter, context.combat, scene);
}

QGraphicsItemGroup *CardInfo::generateCardBackGraphicsItem(Context &context, QGraphicsScene *scene)
{
    const double frameRatio = .7;
    const double titleRatio = .3;

    QGraphicsItemGroup *group = new QGraphicsItemGroup;
    QGraphicsPixmapItem *background = new QGraphicsPixmapItem(group);
    background->setPixmap(context.cardBack.background);

    QGraphicsPixmapItem *frame = new QGraphicsPixmapItem(group);
    frame->setPixmap(context.cardBack.foreground);

    QGraphicsPixmapItem *title = new QGraphicsPixmapItem(group);
    title->setPixmap(context.cardBack.epicDuelsTitle);

    scene->addItem(group);

    int frameY = background->boundingRect().height() * frameRatio;
    frame->moveBy(0, frameY);

    int titleY = frameY;
    int titleX = background->boundingRect().width() * titleRatio;
    title->moveBy(titleX, titleY);

    return group;
}

QGraphicsItemGroup *CardInfo::generateCombatCard(const Context::Character &character, const Context::CombatInfo &combat, QGraphicsScene *scene)
{
    QGraphicsItemGroup *group = new QGraphicsItemGroup;
    QGraphicsPixmapItem *background = new QGraphicsPixmapItem(group);
    background->setPixmap(character.regularPortrait);

    QGraphicsPixmapItem *frame = new QGraphicsPixmapItem(group);
    frame->setPixmap(combat.frame);

    QFont font = combat.font;
    QGraphicsTextItem * attackItem = new QGraphicsTextItem(group);
    attackItem->setPlainText(QString::number(attack));
    attackItem->setFont(font);
    attackItem->setDefaultTextColor(QColor(Qt::white));

    QGraphicsTextItem *defenseItem = new QGraphicsTextItem(group);
    defenseItem->setPlainText(QString::number(defense));
    defenseItem->setFont(font);
    defenseItem->setDefaultTextColor(QColor(Qt::white));

    scene->addItem(group);

    QPointF attackPosition = combat.attackPosition();
    attackItem->moveBy(attackPosition.x(), attackPosition.y());

    QPointF defensePosition = combat.defensePosition();
    defenseItem->moveBy(defensePosition.x(), defensePosition.y());

    return group;
}
