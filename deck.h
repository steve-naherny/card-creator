#ifndef DECK_H
#define DECK_H

// Project
#include "cardinfo.h"
#include "context.h"

// Qt
#include <QString>
#include <QPointer>

class Deck
{
public:
  Deck();

  void load(const QString &path)
  {

  }

  void addSpecial(const QString &title, const QString &text);

  void addSuper(const QString &title, const QString &text, int attack = 0, int defense = 0);

  void addCombat(int attack, int defense);

  void addMinorCombat(int attack, int defense);

  QList<QPointer<CardInfo>> cards;
  Context context;
};

#endif // DECK_H
