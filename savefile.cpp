// Project
#include "savefile.h"

// Qt
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDir>

Context::Image SaveFile::retrieveImage(const QString &imageName, const QSize &size)
{
    QString fullImagePath = path + "/" + imageName + ".png";
    QPixmap pixmap = QPixmap(fullImagePath).scaled(size, Qt::KeepAspectRatioByExpanding);
    if(pixmap.isNull())
    {
        fullImagePath = path + "/" + imageName + ".jpg";
        pixmap = QPixmap(fullImagePath).scaled(size, Qt::KeepAspectRatioByExpanding);
    }

    Context::Image image;
    image.path = fullImagePath;
    image.pixmap = pixmap;
    image.size = size;
    return image;
}

void SaveFile::load(Deck &deck, const QString &_path)
{
    path = _path;
    QFile file(path + "/data.json");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Couldn't open save file.");
    }
    QString contents = file.readAll();
    QJsonObject json = QJsonDocument::fromJson(contents.toUtf8()).object();

    loadContext(deck.context, json);
    loadCards(deck, json);
    loadImages(deck.context);
}

void SaveFile::loadContext(Context &context, QJsonObject &json)
{
    auto mainCharacter = json["mainCharacter"].toObject();
    context.mainCharacter.name = mainCharacter["name"].toString();
    context.mainCharacter.health = mainCharacter["health"].toInt();

    auto minorCharacter = json["minorCharacter"].toObject();
    context.minorCharacter.name =minorCharacter["name"].toString();
    context.minorCharacter.health = minorCharacter["health"].toInt();

    auto special = json["special"].toObject();
    context.special.font = QFont(special["font"].toString());

    auto unique = json["unique"].toObject();
    context.unique.font = QFont(special["font"].toString());
}

void SaveFile::loadCards(Deck &deck, QJsonObject &json)
{
    auto cards = json["cards"].toArray();
    for(auto jsonRef : cards)
    {
        auto cardObject = jsonRef.toObject();
        auto card = deck.generateCard(cardObject["className"].toString());
        card->playType = (CardInfo::PlayType)cardObject["playType"].toInt();
        card->attack = cardObject["attack"].toString();
        card->defense = cardObject["defense"].toString();
        card->description = cardObject["description"].toString();
        card->title = cardObject["title"].toString();
    }
}

void SaveFile::loadImages(Context &context)
{
    QSize cardDimensions = context.cardSize();
    context.cardBack.background = retrieveImage("cardBack.background", cardDimensions);
    context.cardBack.foreground = retrieveImage("cardBack.foreground", context.cardBack.foreGroundSize());
    context.mainCharacter.regularPortrait = retrieveImage("mainCharacter.regularPortrait", cardDimensions);
    context.mainCharacter.specialPortrait = retrieveImage("mainCharacter.specialPortrait", cardDimensions);
    context.minorCharacter.regularPortrait = retrieveImage("minorCharacter.regularPortrait", cardDimensions);
    context.minorCharacter.specialPortrait = retrieveImage("minorCharacter.specialPortrait", cardDimensions);
    context.special.frame = retrieveImage("special.frame", cardDimensions);
    context.unique.frame = retrieveImage("unique.frame", cardDimensions);
    context.unique.defenseFrame = retrieveImage("unique.defenseFrame", context.unique.frameSize());
    context.unique.attackFrame = retrieveImage("unique.attackFrame", context.unique.frameSize());
    context.combat.frame = retrieveImage("combat.frame", context.combat.frameSize());
}

void SaveFile::saveContext(Context &context, QJsonObject &json)
{
    QJsonObject mainCharacter
    {
        {"name", context.mainCharacter.name},
        {"health", context.mainCharacter.health}
    };
    json.insert("mainCharacter", mainCharacter);

    QJsonObject minorCharacter
    {
        {"name", context.minorCharacter.name},
        {"health", context.minorCharacter.health}
    };
    json.insert("minorCharacter", minorCharacter);
    QJsonObject special
    {
        {"font", context.special.font.toString()}
    };
    json.insert("special", special);

    QJsonObject unique
    {
        {"font", context.unique.font.toString()},
        {"frame", context.unique.frame.path }
    };
    json.insert("unique", unique);
}

void SaveFile::saveCards(const QList<QPointer<CardInfo>> &cardInfoPointers, QJsonObject &json)
{
    QJsonArray cards;
    for(auto cardInfoPointer : cardInfoPointers)
    {
        QJsonObject card
        {
            {"attack", cardInfoPointer->attack},
            {"defense", cardInfoPointer->defense},
            {"description", cardInfoPointer->description},
            {"playType", cardInfoPointer->playType},
            {"title", cardInfoPointer->title},
            {"className", cardInfoPointer->cardType()},
        };
        cards.append(card);
    }
    json.insert("cards", cards);
}

void SaveFile::saveImages(Context &context)
{
    registerImage(context.special.frame.path, "specialFrame");
    registerImage(context.cardBack.background.path, "cardBack.background");
    registerImage(context.cardBack.foreground.path, "cardBack.foreground");
    registerImage(context.mainCharacter.regularPortrait.path, "mainCharacter.regularPortrait");
    registerImage(context.mainCharacter.specialPortrait.path, "mainCharacter.specialPortrait");
    registerImage(context.minorCharacter.regularPortrait.path, "minorCharacter.regularPortrait");
    registerImage(context.minorCharacter.specialPortrait.path, "minorCharacter.specialPortrait");
    registerImage(context.special.frame.path, "special.frame");
    registerImage(context.unique.defenseFrame.path, "unique.defenseFrame");
    registerImage(context.unique.attackFrame.path, "unique.attackFrame");
    registerImage(context.combat.frame.path, "combat.frame");
}

QString SaveFile::registerImage(const QString &imagePath, const QString &imageName)
{
    QString outputPath = path + "/" + imageName + ".png";
    QFile::copy(imagePath, outputPath);
    return imageName;
}

void SaveFile::save(Deck &deck, const QString &_path)
{
    if(_path.isEmpty() && path.isEmpty())
        return;
    else if(!_path.isEmpty())
    {
        path = _path;
    }

    if(!QDir().exists(path))
        QDir().mkdir(path);

    QFile file(path + "/data.json");
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
    }

    QJsonObject json;
    saveContext(deck.context, json);
    saveCards(deck.cards, json);
    file.write(QJsonDocument(json).toJson());

    saveImages(deck.context);
}
