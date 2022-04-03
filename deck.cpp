// Project
#include "deck.h"
#include "cardinfo.h"

// Qt
#include <QPointer>

QPointer<CardInfo> Deck::generateCard(const QString &cardType)
{
    QPointer<CardInfo> result;
    if(cardType == MainUniqueCard().cardType())
    {
        result = new MainUniqueCard();
    }
    else if(cardType == MinorUniqueCard().cardType())
    {
        result = new MinorUniqueCard();
    }
    else if(cardType == MainSpecialCard().cardType())
    {
        result = new MainSpecialCard();
    }
    else if(cardType == MinorSpecialCard().cardType())
    {
        result = new MinorSpecialCard();
    }
    else if(cardType == MinorCombatCard().cardType())
    {
        result = new MinorCombatCard();
    }
    else if(cardType == MainCombatCard().cardType())
    {
        result = new MainCombatCard();
    }
    cards.append(result);
    return result;
}

void Deck::addMainUnique(const QString &title, CardInfo::PlayType playType, const QString &description, const QString &attack, const QString &defense)
{
    QPointer<CardInfo> i = new MainUniqueCard;
    i->description = description;
    i->title = title;
    i->playType = playType;
    i->attack = attack;
    i->defense = defense;
    cards.append(i);
}

void Deck::addMinorUnique(const QString &title, CardInfo::PlayType playType, const QString &description, const QString &attack, const QString &defense)
{
    QPointer<CardInfo> i = new MinorUniqueCard;
    i->description = description;
    i->title = title;
    i->playType = playType;
    i->attack = attack;
    i->defense = defense;
    cards.append(i);
}

void Deck::addMainSpecial(const QString &title, CardInfo::PlayType playType, const QString &text)
{
    QPointer<CardInfo> i = new MainSpecialCard;
    i->description = text;
    i->title = title;
    i->playType = playType;
    cards.append(i);
}

void Deck::addMinorSpecial(const QString &title, CardInfo::PlayType playType, const QString &text)
{
    QPointer<CardInfo> i = new MinorSpecialCard;
    i->description = text;
    i->title = title;
    i->playType = playType;
    cards.append(i);
}

void Deck::addMainCombat(const QString &attack, const QString &defense)
{
    QPointer<CardInfo> i = new MainCombatCard;
    i->attack = attack;
    i->defense = defense;
    cards.append(i);
}

void Deck::addMinorCombat(const QString &attack, const QString &defense)
{
    QPointer<CardInfo> i = new MinorCombatCard;
    i->attack = attack;
    i->defense = defense;
    cards.append(i);
}
