// Project
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "scene.h"
#include "context.h"

// Qt
#include <QGraphicsView>
#include <QStandardPaths>
#include <QPixmap>

void load(Context &c)
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/starwars-epic-duels/";
    QPixmap test = QPixmap(path + "/test.png");
    c.backBorder = test;

    QSize cardDimensions = c.cardSize();

    c.cardBack.background = QPixmap(path + "/background.jpg").scaled(cardDimensions, Qt::KeepAspectRatioByExpanding);;
    c.cardBack.epicDuelsTitle = QPixmap(path + "/title.png");;
    c.cardBack.foreground = QPixmap(path + "/frame.png");;

    c.combat.frame = QPixmap(path + "/combat.frame.png").scaled(c.combat.frameSize(), Qt::KeepAspectRatioByExpanding);
    c.combat.font = QFont("calibri", 10, 2);

    c.backBorder = test;
    c.specialFrame = test;
    c.mainCharacter.cardBackPortrait = test;
    c.mainCharacter.specialPortrait = test;
    c.mainCharacter.regularPortrait = QPixmap(path + "/background.jpg").scaled(cardDimensions, Qt::KeepAspectRatioByExpanding);
    c.mainCharacter.health = 20;
    c.mainCharacter.specialPortrait = test;
    c.mainCharacter.name = "Qui Gon Gin";

    c.minorCharacter.cardBackPortrait = test;
    c.minorCharacter.specialPortrait = test;
    c.minorCharacter.regularPortrait = QPixmap(path + "/minor.png").scaled(cardDimensions, Qt::KeepAspectRatioByExpanding); //TEMP
    c.minorCharacter.health = 20;
    c.minorCharacter.specialPortrait = test;
    c.minorCharacter.name = "Ahsoka Tano";
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsView *view = new QGraphicsView(this);
    Scene *scene = new Scene;
    view->setScene(scene);

    Context &c = scene->d.context;
    load(c);

    Deck &d = scene->d;
    d.addCombat(3,3);
    d.addCombat(4,2);
    d.addCombat(5,1);
    d.addCombat(2,4);

//    d.addSpecial("title", "text");
//    d.addSpecial("title", "text");
//    d.addSpecial("title", "text");
//    d.addSpecial("title", "text");

//    d.addSuper("title", "text");
//    d.addSuper("title", "text", 10);
//    d.addSuper("title", "text", 0, 10);
//    d.addSuper("title", "text");

    d.addMinorCombat(3,3);
    d.addMinorCombat(3,1);
    d.addMinorCombat(1,3);
    d.addMinorCombat(1,3);

    scene->refresh();
    view->move(0,-10000);

    setCentralWidget(view);
}

MainWindow::~MainWindow()
{
    delete ui;
}

