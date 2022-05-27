#include "mainwindow.h"
#include "collectionviewer.h"
#include <QGuiApplication>
#include <QScreen>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QToolBar>
#include <QTreeWidget>
#include <iostream>
#include "camera.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    this->setWindowState(Qt::WindowMaximized);
    this->setToolButtonStyle(Qt::ToolButtonFollowStyle);

    model = new CollectionModel(this);
    camera = new Camera(this, Qt::FramelessWindowHint);

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    mainLayout = new QHBoxLayout(centralWidget);

    scroller = new CollectionViewer(model, this);
    editor = new ScreenshotEditor(model, this);

    QObject::connect(scroller->GetView()->selectionModel(), &QItemSelectionModel::currentChanged,
                     editor, &ScreenshotEditor::ChangeView);

    SetupToolbar();

    editAreaLayout = new QGridLayout();
    editAreaLayout->addWidget(toolbar);
    editAreaLayout->addWidget(editor);

    mainLayout->addWidget(scroller, 1);
    mainLayout->addLayout(editAreaLayout, 4);
}

MainWindow::~MainWindow() {
    delete(camera);
    delete(scroller);
    delete(toolbar);
    delete(editor);
    delete(mainLayout);
    delete(editAreaLayout);
    delete(centralWidget);
    delete(model);
}

void MainWindow::AddScreenshot(QPixmap* img) {
    /*
    this->setVisible(false);
    QScreen *screen = QGuiApplication::primaryScreen(); //may not work on iOS(?)
    this->setVisible(true);
    if (screen) {
        QPixmap* ss = new QPixmap(screen->grabWindow(0));
        model->Add(ss);
        delete(ss);
    }*/
}

void MainWindow::ParseToolbarSignal(QAction* action) {
    QString text = action->iconText();
    if (text == DRAW) {
        std::cout << "activate drawing tool" << std::endl;
    } else if (text == ERASE) {
        std::cout << "activate eraser tool" << std::endl;
    } else if (text == CROP) {
        std::cout << "activate cropping tool" << std::endl;
    } else if (text == NEW_COPY) {
        QPixmap* img;
        try {
            img = new QPixmap(editor->GetCurrImg()->data(Qt::DecorationRole).value<QPixmap>());
        } catch (_exception& e) {
            throw std::domain_error("MainWindow::ParseToolbarSignal - QVariant conversion failure");
        }
        QStandardItem* parent = model->FindParent(editor->GetCurrImg());
        model->Add(img, parent);
    } else if (text == DELETE) {
        std::cout << "delete the child image or the whole set of images if the parent was selected" << std::endl;
    } else if (text == NEW_SCREENSHOT) {
        camera->setVisible(true);
    }
}

void MainWindow::SetupToolbar() {
    toolbar = new QToolBar(this);
    toolbar->addAction(DRAW);
    toolbar->addAction(ERASE);
    toolbar->addAction(CROP);
    toolbar->addSeparator();
    toolbar->addAction(SAVE_TO_FILE, editor, &ScreenshotEditor::Save);
    toolbar->addAction(NEW_COPY);
    toolbar->addAction(DELETE);
    toolbar->addSeparator();
    toolbar->addAction(NEW_SCREENSHOT);

    QObject::connect(toolbar, &QToolBar::actionTriggered,
                     this, &MainWindow::ParseToolbarSignal);
}







