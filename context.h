#ifndef CONTEXT_H
#define CONTEXT_H

// Qt
#include <QString>
#include <QPixmap>
#include <QFont>

// These values need to be changed to where the user can set them.
static int cardWidth = 450;
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

    struct Image
    {
        Image()
        {

        }
        Image(Image &other)
        {
            path = other.path;
            pixmap = other.pixmap;
            size = other.size;
        }
        QString path;
        QPixmap pixmap;
        QSize size;
    };

    QString path;
    struct Character
    {
        QString name;
        int health = 0;
        Image specialPortrait;
        Image regularPortrait;
    };

    Character mainCharacter, minorCharacter;

    struct CardBack
    {
        Image foreground;
        Image background;

        static QPointF foreGroundPosition()
        {
            const double yRatio = 0.75;
            auto s = cardSize();
            return QPointF(0, s.height() * yRatio);
        }

        static QSize foreGroundSize()
        {
            const double yRatio = 0.25;
            auto s = cardSize();
            return QSize(s.width(), s.height() * yRatio);
        }
    } cardBack;

    struct SpecialInfo
    {
        QFont font;
        Image frame;
    } special;

    struct UniqueInfo
    {
        QFont font;
        Image frame;
        Image attackFrame;
        Image defenseFrame;


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
        Image frame;

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
};

#endif // CONTEXT_H
