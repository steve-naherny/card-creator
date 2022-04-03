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
    enum PlayType { None, OnTurn, WhenDefending, WhenAttacking, WhenAttackingDefending };
    QString defense;
    QString attack;
    QString description;
    QString title;
    PlayType playType = None;
    static QString toString(PlayType pt);
    static QGraphicsItemGroup *generateCardBackGraphicsItem(Context &context, QGraphicsScene *scene);
    QGraphicsItemGroup *generateCombatCard(const Context::Character &character, const Context::CombatInfo &info, QGraphicsScene *scene);
    QGraphicsItemGroup *generateSpecialCard(const Context::Character &character, const Context::SpecialInfo &info, QGraphicsScene *scene);
    QGraphicsItemGroup *generateUniqueCard(const Context::Character &character, const Context::UniqueInfo &info, QGraphicsScene *scene);
    virtual QGraphicsItemGroup* generateGraphicsItem(Context &, QGraphicsScene *) { return nullptr; };
    virtual QString cardType() { return "Invalid"; }
};

class MainUniqueCard : public CardInfo
{
    public:
    QString cardType() { return "MainUnique"; }
    QGraphicsItemGroup* generateGraphicsItem(Context &context, QGraphicsScene *scene);
};

class MinorUniqueCard : public CardInfo
{
    public:
    QString cardType() { return "MinorUnique"; }
    QGraphicsItemGroup* generateGraphicsItem(Context &context, QGraphicsScene *scene);
};

class MainSpecialCard : public CardInfo
{
    public:
    QString cardType() { return "MainSpecial"; }
    QGraphicsItemGroup* generateGraphicsItem(Context &context, QGraphicsScene *scene);
};

class MinorSpecialCard : public CardInfo
{
    public:
    QString cardType() { return "MinorSpecial"; }
    QGraphicsItemGroup* generateGraphicsItem(Context &context, QGraphicsScene *scene);
};

class MinorCombatCard : public CardInfo
{
    public:
    QString cardType() { return "MinorCombat"; }
    QGraphicsItemGroup* generateGraphicsItem(Context &context, QGraphicsScene *scene);
};

class MainCombatCard : public CardInfo
{
public:
    QString cardType() { return "MainCombat"; }
    QGraphicsItemGroup* generateGraphicsItem(Context &context, QGraphicsScene *scene);
};
#endif // CARDINFO_H
