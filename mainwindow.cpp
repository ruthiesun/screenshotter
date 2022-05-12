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

    SetupScrollbar();

    editAreaLayout = new QGridLayout();
    SetupToolbar();
    editAreaLayout->addWidget(toolbar);
    SetupEditor();
    editAreaLayout->addWidget(editor);

    mainLayout->addWidget(scroller, 1);
    mainLayout->addLayout(editAreaLayout, 4);
}

MainWindow::~MainWindow() {
    delete(scroller); //!!!
}

void MainWindow::AddScreenshot(QPixmap* img) {
    //call scroller's add method
}

void MainWindow::SetupScrollbar() {
    scroller = new CollectionScroller(this);
    QPixmap* tempImg= new QPixmap(100,200);
    tempImg->fill(Qt::blue);
    scroller->Add(tempImg);

    QPixmap* tempImg2= new QPixmap(3,100);
    tempImg->fill(Qt::yellow);
    scroller->Add(tempImg);


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
    toolbar->addAction("Delete");
}

void MainWindow::SetupEditor() {
    QScreen *screen = QGuiApplication::primaryScreen();
    /*if (screen) {
        QPixmap originalPixmap = screen->grabWindow(0);
        editor = new ScreenshotEditor(this, &originalPixmap);
    } else {*/
        QPixmap* tempImg = new QPixmap(500, 500);
        tempImg->fill(Qt::green);
        editor = new ScreenshotEditor(tempImg, this);
    //}



}



