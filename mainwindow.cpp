#include "mainwindow.h"
#include "collectionviewer.h"
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

    model = new CollectionModel(this);

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    mainLayout = new QHBoxLayout(centralWidget);

    scroller = new CollectionViewer(model, this);
    editor = new ScreenshotEditor(model, this);

    QObject::connect(scroller->GetView()->selectionModel(), &QItemSelectionModel::currentChanged, //!!!
                     editor, &ScreenshotEditor::ChangeView);

    SetupToolbar();

    editAreaLayout = new QGridLayout();
    editAreaLayout->addWidget(toolbar);
    editAreaLayout->addWidget(editor);

    mainLayout->addWidget(scroller, 1);
    mainLayout->addLayout(editAreaLayout, 4);
}

MainWindow::~MainWindow() {
    delete(scroller); //!!!
}

void MainWindow::AddScreenshot() {
    QScreen *screen = QGuiApplication::primaryScreen();
    if (screen) {
        QPixmap* ss = new QPixmap(screen->grabWindow(0));
        scroller->Add(ss);
        delete(ss);
    }
}

void MainWindow::ParseToolbarSignal(QAction* action) {
    //std::cout << action->iconText().toStdString() << std::endl;
    QString text = action->iconText();
    if (text == DRAW) {
        std::cout << "active drawing tool - TEMP SS" << std::endl;
        AddScreenshot();
    } else if (text == ERASE) {
        std::cout << "activate eraser tool" << std::endl;
    } else if (text == CROP) {
        std::cout << "activate cropping tool" << std::endl;
    } else if (text == SAVE_CHANGES) {
        std::cout << "save changes to current pic" << std::endl;
    } else if (text == SAVE_TO_FILE) {
        std::cout << "save to disk (let user choose file location" << std::endl;
    } else if (text == NEW_COPY) {
        //UNTESTED
        std::cout << "duplicate screenshot and open it" << std::endl;
        QPixmap* ss = editor->GetCurrImg()->data(Qt::UserRole).value<QPixmap*>();
        QStandardItem* parent = editor->GetCurrImg()->parent();
        scroller->Add(ss, parent);
    } else if (text == DELETE) {
        std::cout << "delete the child image or the whole set of images if the parent was selected" << std::endl;
    }
}

void MainWindow::SetupToolbar() {
    toolbar = new QToolBar(this);
    toolbar->addAction(DRAW);
    toolbar->addAction(ERASE);
    toolbar->addAction(CROP);
    toolbar->addSeparator();
    toolbar->addAction(SAVE_CHANGES);
    toolbar->addAction(SAVE_TO_FILE);
    toolbar->addAction(NEW_COPY);
    toolbar->addAction(DELETE);

    QObject::connect(toolbar, &QToolBar::actionTriggered,
                     this, &MainWindow::ParseToolbarSignal);



}





