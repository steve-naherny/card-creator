#ifndef CONTEXT_H
#define CONTEXT_H


#include <QString>
#include <QPixmap>
#include <QFont>
// These values need to be changed to where the user can set them.
static int cardWidth = 200;
static double cardHeightRatio = 1.36;

struct Context
{
  inline static QSize cardSize()
  {
      return QSize(cardWidth, cardWidth * cardHeightRatio);
  };

  QString path;


  struct Character
  {
    QString name;
    int health = 0;
    QPixmap healthBorder;
    QPixmap specialPortrait;
    QPixmap regularPortrait;
    QPixmap cardBackPortrait;
  };

  Character mainCharacter, minorCharacter;

  struct CardBack
  {
    QPixmap foreground;
    QPixmap background;
    QPixmap epicDuelsTitle;
  } cardBack;

  struct CombatInfo
  {
      QPixmap frame;
      QFont font;

      static QSize frameSize()
      {
          const double xRatio = 0.3;
          const double yRatio = 0.3;
          auto s = cardSize();
          return QSize(s.width() * xRatio, s.height() * yRatio);
      }

      static QPointF attackPosition()
      {
          const double xRatio = 0.40;
          const double yRatio = 0.27;
          auto s = frameSize();
          return QPointF(s.width() * xRatio, s.height() * yRatio);
      }


      static QPointF defensePosition()
      {
          const double xRatio = 0.40;
          const double yRatio = 0.57;
          auto s = frameSize();
          return QPointF(s.width() * xRatio, s.height() * yRatio);
      }
  } combat;

  QPixmap specialFrame;
  QPixmap backBorder;

};

#endif // CONTEXT_H
