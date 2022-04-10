// Project
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "scene.h"
#include "context.h"
#include "savefile.h"
#include "view.h"

// Qt
#include <QGraphicsView>
#include <QStandardPaths>
#include <QPixmap>
#include <QDebug>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QDockWidget>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QFileDialog>
#include <QtPrintSupport/QPrintPreviewDialog>

#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGraphicsView *view = new QGraphicsView(this);
    Graphics_view_zoom *zoom = new Graphics_view_zoom(view);
    scene = new Scene;
    view->setScene(scene);

    QMenu *menu = new QMenu("File");
    auto openAction = menu->addAction("Open...");
    connect(openAction, &QAction::triggered, this, [this](){
        QString defaultPath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/starwars-epic-duels/";
        QString selectedFolder = QFileDialog::getExistingDirectory(this, "Select File", defaultPath);
        if(!selectedFolder.isEmpty())
        {
            scene->clear();
            saveFile.load(scene->d, selectedFolder);
            scene->refresh();
        }
    });

    auto exportAction = menu->addAction("Export...");
    connect(exportAction, &QAction::triggered, this, [this](){
        QPrinter *printer = new QPrinter(QPrinter::PrinterMode::PrinterResolution);
        QPrintPreviewDialog dialog(printer);
        connect(&dialog, &QPrintPreviewDialog::paintRequested, [&](QPrinter *previewPrinter) {
            QPainter painter(previewPrinter);
            double rectThird = scene->sceneRect().height() / 3;
            auto sceneRect = scene->sceneRect();
            auto rect = sceneRect;
            rect.setHeight(sceneRect.height() / 3);
            scene->render(&painter,QRectF(), rect);
            previewPrinter->newPage();

            rect.moveTop(rectThird);
            scene->render(&painter,QRectF(), rect);
            previewPrinter->newPage();

            rect.moveTop(rectThird * 2);
            scene->render(&painter,QRectF(), rect);
            previewPrinter->newPage();

            rect.moveTop(rectThird * 3);
            scene->render(&painter,QRectF(), rect);
        });
        dialog.exec();
    });

    auto saveAsAction = menu->addAction("Save As...");
    connect(saveAsAction, &QAction::triggered, this, [this](){
        QString path = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/starwars-epic-duels";
        QString selected = QFileDialog::getExistingDirectory(this, "Select File", path);
        if(!selected.isEmpty())
        {
            saveFile.save(scene->d, selected);
        }
    });

    auto saveAction = menu->addAction("Save");
    connect(saveAction, &QAction::triggered, this, [this]() {
        saveFile.save(scene->d);
    });

    auto quitAction = menu->addAction("Exit");
    connect(quitAction, &QAction::triggered, []() {
        qApp->quit();
    });

    //TEST CODE
    QString selectedFolder = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/starwars-epic-duels/test";
    saveFile.load(scene->d, selectedFolder);
    scene->refresh();

    menuBar()->addMenu(menu);
    setCentralWidget(view);

    connectImageButtons();
    connectCardGroup();
    connectMainGroup();
    connectMinorGroup();
    connectOtherGroup();
}

MainWindow::~MainWindow()
{
    delete ui;
}

Context::Image selectAndLoadImage(QToolButton *b, Context::Image image)
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/starwars-epic-duels";
    QString selected = QFileDialog::getOpenFileName(b, "Select Image", path, "*.png");
    if(!selected.isEmpty())
    {
        image.path = selected;
        image.pixmap = QPixmap(selected).scaled(image.size, Qt::KeepAspectRatioByExpanding);
        b->setIcon(QIcon(selected));
    }
    return image;
}

void selectAndLoadImage_undeped(QToolButton *b, Context::Image *image)
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/starwars-epic-duels";
    QString selected = QFileDialog::getOpenFileName(b, "Select Image", path, "*.png");
    if(!selected.isEmpty())
    {
        image->path = selected;
        image->pixmap = QPixmap(selected).scaled(image->size, Qt::KeepAspectRatioByExpanding);
        b->setIcon(QIcon(selected));
    }
}

void MainWindow::connectImageButtons()
{
    QList<QPair<QToolButton*, Context::Image*>> buttonImagePairs = {
        {ui->mainRegularPortraitButton, &(scene->d.context.mainCharacter.regularPortrait)},
        {ui->minorSpecialPortraitButton, &(scene->d.context.minorCharacter.specialPortrait)},
        {ui->attackSymbolButton, &(scene->d.context.unique.attackFrame)},
        {ui->defenseSymbolButton, &(scene->d.context.unique.defenseFrame)},
        {ui->CombatFrameButton, &(scene->d.context.combat.frame)},
        {ui->cardbackBackgroundButton, &(scene->d.context.cardBack.background)},
        {ui->cardbackForegroundButton, &(scene->d.context.cardBack.foreground)},
        {ui->uniqueFrameButton, &(scene->d.context.unique.frame)},
        {ui->SpecialFrameButton, &(scene->d.context.special.frame)},
        {ui->mainRegularPortraitButton, &(scene->d.context.mainCharacter.regularPortrait)},
        {ui->mainRegularPortraitButton, &(scene->d.context.mainCharacter.regularPortrait)}
    };

    for(auto pair : buttonImagePairs)
    {
        connect(pair.first, &QPushButton::clicked, [this, pair]() {
            selectAndLoadImage_undeped(pair.first, pair.second);
            scene->refresh();
        });
    }
}

void MainWindow::connectCardGroup()
{
    connect(ui->mainCombatButton, &QPushButton::clicked, [this](){
        scene->d.addMainCombat("5", "5");
        scene->refresh();
    });

    connect(ui->minorCombatButton, &QPushButton::clicked, [this](){
        scene->d.addMinorCombat("5", "5");
        scene->refresh();
    });

    connect(ui->mainSpecialButton, &QPushButton::clicked, [this](){
        scene->d.addMainSpecial("", CardInfo::PlayType::WhenAttackingDefending, "");
        scene->refresh();
    });

    connect(ui->minorSpecialButton, &QPushButton::clicked, [this](){
        scene->d.addMainSpecial("", CardInfo::PlayType::WhenAttackingDefending, "");
        scene->refresh();
    });

    connect(ui->mainUniqueButton, &QPushButton::clicked, [this](){
        scene->d.addMainUnique("", CardInfo::PlayType::WhenAttackingDefending, "", "5", "5");
        scene->refresh();
    });

    connect(ui->minorUniqueButton, &QPushButton::clicked, [this](){
        scene->d.addMinorUnique("", CardInfo::PlayType::WhenAttackingDefending, "", "5", "5");
        scene->refresh();
    });
}

void MainWindow::connectMainGroup()
{
    connect(ui->mainHealth, &QSpinBox::editingFinished, [this]() {
        scene->d.context.mainCharacter.health = ui->mainHealth->value();
        scene->refresh();
    });

    connect(ui->mainName, &QLineEdit::editingFinished, [this](){
        scene->d.context.mainCharacter.name = ui->mainName->text();
        scene->refresh();
    });
}

void MainWindow::connectMinorGroup()
{
    connect(ui->minorHealth, &QSpinBox::editingFinished, [this]() {
        scene->d.context.minorCharacter.health = ui->minorHealth->value();
        scene->refresh();
    });

    connect(ui->minorName, &QLineEdit::editingFinished, [this](){
        scene->d.context.minorCharacter.name = ui->minorName->text();
        scene->refresh();
    });
}

void MainWindow::connectOtherGroup()
{

}

