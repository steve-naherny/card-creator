#ifndef SAVEFILE_H
#define SAVEFILE_H

// Project
#include "context.h"
#include "deck.h"
#include "cardinfo.h"

class SaveFile
{
public:
    void save(Deck &deck, const QString &path = "");
    void load(Deck &deck, const QString &path);

private:
    void loadContext(Context &context, QJsonObject &json);
    void loadCards(Deck &deck, QJsonObject &json);
    void loadImages(Context &context);

    void saveContext(Context &context, QJsonObject &json);
    void saveCards(const QList<QPointer<CardInfo>> &cards, QJsonObject &json);
    void saveImages(Context &context);
    QString registerImage(const QString &imagePath, const QString &imageName);
    Context::Image retrieveImage(const QString &imageName, const QSize &size);
    QString path;
};

#endif // SAVEFILE_H
