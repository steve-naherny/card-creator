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
  void addMainUnique(const QString &title, CardInfo::PlayType playType, const QString &description, const QString &attack = QString(), const QString &defense = QString());

  void addMinorUnique(const QString &title, CardInfo::PlayType playType, const QString &description, const QString &attack = QString(), const QString &defense = QString());

  void addMinorSpecial(const QString &title, CardInfo::PlayType playType, const QString &description);

  void addMainSpecial(const QString &title, CardInfo::PlayType playType, const QString &description);

  void addMainCombat(const QString &attack, const QString &defense);

  void addMinorCombat(const QString &attack, const QString &defense);

  QPointer<CardInfo> generateCard(const QString &cardType);

  QList<QPointer<CardInfo>> cards;
  Context context;
};

#endif // DECK_H
