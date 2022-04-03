#ifndef CONTEXT_H
#define CONTEXT_H

// Qt
#include <QString>
#include <QPixmap>
#include <QFont>

// These values need to be changed to where the user can set them.
static int cardWidth = 200;
static double cardHeightRatio = 1.36;

struct Context
{
    void load(const QString &path);
    void save(const QString &path);

    inline static QSize cardSize()
    {
        return QSize(cardWidth, cardWidth * cardHeightRatio);
    };

    static QPointF namePosition()
    {
        const double xRatio = 0.40;
        const double yRatio = 0.48;
        auto s = cardSize();
        return QPointF(s.width() * xRatio, s.height() * yRatio);
    }

    static QPointF titlePosition()
    {
        const double xRatio = 0.30;
        const double yRatio = 0.60;
        auto s = cardSize();
        return QPointF(s.width() * xRatio, s.height() * yRatio);
    }

    static QPointF playTypePosition()
    {
        const double xRatio = 0.20;
        const double yRatio = 0.68;
        auto s = cardSize();
        return QPointF(s.width() * xRatio, s.height() * yRatio);
    }

    static QPointF descriptionPosition()
    {
        const double xRatio = 0.15;
        const double yRatio = 0.75;
        auto s = cardSize();
        return QPointF(s.width() * xRatio, s.height() * yRatio);
    }

    inline static QFont combatFont()
    {
        return QFont("calibri", 14, 4);
    }

    QString path;
    struct Character
    {
        QString name;
        int health = 0;
        QPair<QString, QPixmap> specialPortrait;
        QPair<QString, QPixmap> regularPortrait;
    };

    Character mainCharacter, minorCharacter;

    struct CardBack
    {
        QPair<QString, QPixmap> foreground;
        QPair<QString, QPixmap> background;
        QPair<QString, QPixmap> epicDuelsTitle;
    } cardBack;

    struct SpecialInfo
    {
        QFont font;
        QPair<QString, QPixmap> frame;
    } special;

    struct UniqueInfo
    {
        QFont font;
        QPair<QString, QPixmap> frame;
        QPair<QString, QPixmap> attackFrame;
        QPair<QString, QPixmap> defenseFrame;


        static QPointF firstCombatPosition()
        {
            const double xRatio = 0.15;
            const double yRatio = 0.20;
            auto s = cardSize();
            return QPointF(s.width() * xRatio, s.height() * yRatio);
        }

        static QPointF secondCombatPosition()
        {
            const double xRatio = 0.15;
            const double yRatio = 0.40;
            auto s = cardSize();
            return QPointF(s.width() * xRatio, s.height() * yRatio);
        }

        static QPointF firstCombatFramePosition()
        {
            const double xRatio = 0.18;
            const double yRatio = 0.20;
            auto s = cardSize();
            return QPointF(s.width() * xRatio, s.height() * yRatio);
        }

        static QPointF secondCombatFramePosition()
        {
            const double xRatio = 0.18;
            const double yRatio = 0.40;
            auto s = cardSize();
            return QPointF(s.width() * xRatio, s.height() * yRatio);
        }

        static QSize frameSize()
        {
            const double xRatio = 0.25;
            auto s = cardSize();
            int width = s.width() * xRatio;
            return QSize(width, width);
        }

    } unique;

    struct CombatInfo
    {
        QPair<QString, QPixmap> frame;

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
            const double yRatio = 0.26;
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

    QPair<QString, QPixmap> cardBackPortrait;
};

#endif // CONTEXT_H
