// Project
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "scene.h"
#include "context.h"
#include "savefile.h"
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
    Scene *scene = new Scene;
    view->setScene(scene);

    QMenu *menu = new QMenu("File");
    auto openAction = menu->addAction("Open...");
    connect(openAction, &QAction::triggered, this, [this, scene](){
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
    connect(exportAction, &QAction::triggered, this, [scene](){
        QPrintPreviewDialog dialog;
        connect(&dialog, &QPrintPreviewDialog::paintRequested, [&](QPrinter *previewPrinter) {
            QPainter painter(previewPrinter);
            scene->render(&painter);
        });
        dialog.exec();
    });

    auto saveAsAction = menu->addAction("Save As...");
    connect(saveAsAction, &QAction::triggered, this, [this, scene](){
        QString path = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/starwars-epic-duels";
        QString selected = QFileDialog::getExistingDirectory(this, "Select File", path);
        if(!selected.isEmpty())
        {
            saveFile.save(scene->d, selected);
        }
    });

    auto saveAction = menu->addAction("Save");
    connect(saveAction, &QAction::triggered, this, [this, scene]() {
         saveFile.save(scene->d);
    });

    auto quitAction = menu->addAction("Exit");
    connect(quitAction, &QAction::triggered, []() {
        qApp->quit();
    });

    menuBar()->addMenu(menu);
    setCentralWidget(view);
}

MainWindow::~MainWindow()
{
    delete ui;
}

