#ifndef CARDINFO_H
#define CARDINFO_H

// Qt
#include <QString>
#include <QGraphicsItem>
#include <QGraphicsItemGroup>
#include <QGraphicsScene>
#include <QPixmap>

// Project
#include "context.h"

class CardInfo : public QObject
{
public:
    CardInfo() {}
    enum Type { None, Combat, Super, Special, Minor };
    int defense = 0;
    int attack = 0;
    QString text;
    QString title;
    virtual Type type() { return None; };
    static QGraphicsItemGroup *generateCardBackGraphicsItem(Context &context, QGraphicsScene *scene);
    QGraphicsItemGroup *generateCombatCard(const Context::Character &character, const Context::CombatInfo &info, QGraphicsScene *scene);
    virtual QGraphicsItemGroup* generateGraphicsItem(Context &, QGraphicsScene *) { return nullptr; };
};

class SuperCard : public CardInfo
{
    inline Type type()
    {
       return Super;
    }
    QGraphicsItemGroup* generateGraphicsItem(Context &context, QGraphicsScene *scene);
};


class SpecialCard : public CardInfo
{
    inline Type type()
    {
       return Special;
    }
    QGraphicsItemGroup* generateGraphicsItem(Context &context, QGraphicsScene *scene);
};


class MinorCombatCard : public CardInfo
{
    inline Type type()
    {
       return Minor;
    }
    QGraphicsItemGroup* generateGraphicsItem(Context &context, QGraphicsScene *scene);
};

class CombatCard : public CardInfo
{
    inline Type type()
    {
       return Combat;
    }
    QGraphicsItemGroup* generateGraphicsItem(Context &context, QGraphicsScene *scene);
};


#endif // CARDINFO_H
