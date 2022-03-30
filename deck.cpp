// Project
#include "deck.h"
#include "cardinfo.h"
// Qt
#include <QPointer>

Deck::Deck()
{

}

void Deck::addSpecial(const QString &title, const QString &text)
{
    QPointer<CardInfo> i = new SpecialCard;
    i->text = text;
    i->title = title;
    cards.append(i);
}

void Deck::addSuper(const QString &title, const QString &text, int attack, int defense)
{
    QPointer<CardInfo> i = new SuperCard;
    i->text = text;
    i->title = title;
    i->attack = attack;
    i->defense = defense;
    cards.append(i);
}

void Deck::addCombat(int attack, int defense)
{
    QPointer<CardInfo> i = new CombatCard;
    i->attack = attack;
    i->defense = defense;
    cards.append(i);
}

void Deck::addMinorCombat(int attack, int defense)
{
    QPointer<CardInfo> i = new MinorCombatCard;
    i->attack = attack;
    i->defense = defense;
    cards.append(i);
}
