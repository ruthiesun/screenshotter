#include "mainwindow.h"
#include "collectionscroller.h"
#include <QGuiApplication>
#include <QScreen>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QToolBar>
#include <QTreeWidget>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    this->setWindowState(Qt::WindowMaximized);
    this->setToolButtonStyle(Qt::ToolButtonFollowStyle);

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    mainLayout = new QHBoxLayout(centralWidget);

    scroller = new CollectionScroller(this);
    editor = new ScreenshotEditor(this);
    SetupToolbar();

    editAreaLayout = new QGridLayout();
    editAreaLayout->addWidget(toolbar);
    editAreaLayout->addWidget(editor);

    mainLayout->addWidget(scroller, 1);
    mainLayout->addLayout(editAreaLayout, 4);

    //mem leaks
    QPixmap* tempImg= new QPixmap(100,200);
    tempImg->fill(Qt::blue);
    scroller->Add(tempImg);

    QPixmap* tempImg2= new QPixmap(3,100);
    tempImg->fill(Qt::yellow);
    scroller->Add(tempImg);
}

MainWindow::~MainWindow() {
    delete(scroller); //!!!
}

void MainWindow::AddScreenshot() {
    QScreen *screen = QGuiApplication::primaryScreen();
    if (screen) {
        QPixmap* ss = new QPixmap(screen->grabWindow(0));
        //editor = new ScreenshotEditor(ss);
        scroller->Add(ss);
        delete(ss);
    }
}

void MainWindow::UpdateEditor(QPixmap* img) {
    if (editor) {
        delete(editor);
    }
    editor = new ScreenshotEditor(img);
}

void MainWindow::ParseToolbarSignal(QAction* action) {
    std::cout << "action made" << std::endl;
}

void MainWindow::SetupToolbar() {
    toolbar = new QToolBar(this);
    toolbar->addAction("Draw");
    toolbar->addAction("Erase");
    toolbar->addAction("Crop");
    toolbar->addSeparator();
    toolbar->addAction("Save changes");
    toolbar->addAction("Save to file");

    toolbar->addAction("Edit");

    QObject::connect(toolbar, &QToolBar::actionTriggered,
                     this, &MainWindow::ParseToolbarSignal);


    toolbar->addAction("Delete");
}





