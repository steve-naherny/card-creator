#include "cardinfo.h"

// Qt
#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QGraphicsScene>
#include <QMetaEnum>
#include <QTextDocument>

QGraphicsItemGroup *MainUniqueCard::generateGraphicsItem(Context &context, QGraphicsScene *scene)
{
    return generateUniqueCard(context.mainCharacter, context.unique, scene);
}

QGraphicsItemGroup *MinorUniqueCard::generateGraphicsItem(Context &context, QGraphicsScene *scene)
{
    return generateUniqueCard(context.minorCharacter, context.unique, scene);
}

QGraphicsItemGroup *MainSpecialCard::generateGraphicsItem(Context &context, QGraphicsScene *scene)
{
    return generateSpecialCard(context.mainCharacter, context.special, scene);
}

QGraphicsItemGroup *MinorSpecialCard::generateGraphicsItem(Context &context, QGraphicsScene *scene)
{
    return generateSpecialCard(context.minorCharacter, context.special, scene);
}

QGraphicsItemGroup* MinorCombatCard::generateGraphicsItem(Context &context, QGraphicsScene *scene)
{
    return generateCombatCard(context.minorCharacter, context.combat, scene);
}

QGraphicsItemGroup* MainCombatCard::generateGraphicsItem(Context &context, QGraphicsScene *scene)
{
    return generateCombatCard(context.mainCharacter, context.combat, scene);
}

QString CardInfo::toString(PlayType pt)
{
    QString result = "Play ";
    if(pt == OnTurn)
    {
        result += "anytime on your turn.";
    }
    else if(pt == WhenAttacking)
    {
        result += "when you are attacking.";
    }
    else if(pt == WhenAttackingDefending)
    {
        result += "when you are attacking or defending.";
    }
    else if(pt == WhenDefending)
    {
        result += "when you are defending.";
    }
    return result;
}

QGraphicsItemGroup *CardInfo::generateCardBackGraphicsItem(Context &context, QGraphicsScene *scene)
{
    QGraphicsItemGroup *group = new QGraphicsItemGroup;
    QGraphicsPixmapItem *background = new QGraphicsPixmapItem(group);
    background->setPixmap(context.cardBack.background.second);

    QGraphicsPixmapItem *frame = new QGraphicsPixmapItem(group);
    frame->setPixmap(context.cardBack.foreground.second);

    scene->addItem(group);

    QPointF pos = context.cardBack.foreGroundPosition();
    frame->moveBy(pos.x(), pos.y());

    return group;
}

QGraphicsItemGroup *CardInfo::generateCombatCard(const Context::Character &character, const Context::CombatInfo &combat, QGraphicsScene *scene)
{
    QGraphicsItemGroup *group = new QGraphicsItemGroup;
    QGraphicsPixmapItem *background = new QGraphicsPixmapItem(group);
    background->setPixmap(character.regularPortrait.second);

    QGraphicsPixmapItem *frame = new QGraphicsPixmapItem(group);
    frame->setPixmap(combat.frame.second);

    QFont font = Context::combatFont();
    QGraphicsTextItem * attackItem = new QGraphicsTextItem(group);
    attackItem->setPlainText(attack);
    attackItem->setFont(font);
    attackItem->setDefaultTextColor(QColor(Qt::white));

    QGraphicsTextItem *defenseItem = new QGraphicsTextItem(group);
    defenseItem->setPlainText(defense);
    defenseItem->setFont(font);
    defenseItem->setDefaultTextColor(QColor(Qt::white));

    scene->addItem(group);

    QPointF aPos = combat.attackPosition();
    attackItem->moveBy(aPos.x(), aPos.y());

    QPointF dPos = combat.defensePosition();
    defenseItem->moveBy(dPos.x(), dPos.y());

    return group;
}

QGraphicsItemGroup *CardInfo::generateSpecialCard(const Context::Character &character, const Context::SpecialInfo &info, QGraphicsScene *scene)
{
    QGraphicsItemGroup *group = new QGraphicsItemGroup;
    QGraphicsPixmapItem *background = new QGraphicsPixmapItem(group);
    background->setPixmap(character.specialPortrait.second);

    QGraphicsPixmapItem *frame = new QGraphicsPixmapItem(group);
    frame->setPixmap(info.frame.second);

    struct TextData
    {
        QString text;
        QFont font;
        QPointF position;
        QColor color;
    };

    QList<TextData> datas = {
        {character.name,       QFont("calibri", 16, 6),    Context::namePosition(),        QColor(Qt::white)},
        {title,                QFont("calibri", 12, 8),    Context::titlePosition(),       QColor(Qt::white)},
        {toString(playType),   QFont("calibri", 6, 4),    Context::playTypePosition(),    QColor(Qt::black)},
        {description,          QFont("calibri", 10, 2),    Context::descriptionPosition(), QColor(Qt::black)}
    };

    QList<QGraphicsTextItem*> items;
    for(const auto &d : datas)
    {
        QGraphicsTextItem *item = new QGraphicsTextItem(group);
        item->setPlainText(d.text);
        items << item;
    }

    scene->addItem(group);

    for(int i = 0; i < items.size(); i++)
    {
        QGraphicsTextItem *item = items.at(i);
        const auto &d = datas[i];
        QPointF pos = d.position;
        item->moveBy(pos.x(), pos.y());
        item->setTextWidth(Context::cardSize().width() * 0.85);
        item->setDefaultTextColor(d.color);
        item->setFont(d.font);
    }

    return group;
}

QGraphicsItemGroup *CardInfo::generateUniqueCard(const Context::Character &character, const Context::UniqueInfo &info, QGraphicsScene *scene)
{
    QGraphicsItemGroup *group = new QGraphicsItemGroup;
    QGraphicsPixmapItem *background = new QGraphicsPixmapItem(group);
    background->setPixmap(character.specialPortrait.second);

    QGraphicsPixmapItem *frame = new QGraphicsPixmapItem(group);
    frame->setPixmap(info.frame.second);

    struct TextData
    {
        QString text;
        QFont font;
        QPointF position;
        QColor color;
    };

    QList<TextData> datas = {
        {character.name,       QFont("calibri", 16, 6),    Context::namePosition(),        QColor(Qt::white)},
        {title,                QFont("calibri", 12, 8),    Context::titlePosition(),       QColor(Qt::white)},
        {toString(playType),   QFont("calibri", 6, 4),    Context::playTypePosition(),    QColor(Qt::black)},
        {description,          QFont("calibri", 8, 2),    Context::descriptionPosition(), QColor(Qt::black)}
    };

    QList<QPointF> combatPositions = {info.firstCombatPosition(), info.secondCombatPosition()};
    QList<QGraphicsPixmapItem*> combatFrames;
    if(attack.size())
    {
        datas.append({attack,Context::combatFont(),combatPositions.first(), QColor(Qt::white)});
        QGraphicsPixmapItem *combatFrame = new QGraphicsPixmapItem(group);
        combatFrame->setPixmap(info.attackFrame.second);
        combatFrames.append(combatFrame);
    }

    if(defense.size())
    {
        datas.append({defense,Context::combatFont(),combatPositions.last(), QColor(Qt::white)});
        QGraphicsPixmapItem *combatFrame = new QGraphicsPixmapItem(group);
        combatFrame->setPixmap(info.defenseFrame.second);
        combatFrames.append(combatFrame);
    }

    QList<QGraphicsTextItem*> items;
    for(const auto &d : datas)
    {
        QGraphicsTextItem *item = new QGraphicsTextItem(group);
        item->setPlainText(d.text);
        items << item;
    }

    scene->addItem(group);

    for(int i = 0; i < items.size(); i++)
    {
        QGraphicsTextItem *item = items.at(i);
        const auto &d = datas[i];
        QPointF pos = d.position;
        item->moveBy(pos.x(), pos.y());
        item->setTextWidth(Context::cardSize().width() * 0.85);
        item->setDefaultTextColor(d.color);
        item->setFont(d.font);
        item->setZValue(2);
    }

    QList<QPointF> framePositions = {info.firstCombatFramePosition(), info.secondCombatFramePosition()};
    for(auto item : combatFrames)
    {
        QPointF pos = framePositions.takeFirst();
        int x = pos.x() - info.frameSize().width() / 2;
        int y = pos.y() - info.frameSize().height() / 2;
        item->moveBy(x,y);
    }

    return group;
}
