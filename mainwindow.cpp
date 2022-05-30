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
    model = new CollectionModel(this);
    camera = new Camera();
    QObject::connect(camera, &Camera::snapped,
                     this, &MainWindow::addScreenshot);

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    mainLayout = new QHBoxLayout(centralWidget);

    scroller = new CollectionViewer(model, this);
    editor = new ScreenshotEditor(model, this);
    QObject::connect(scroller->selectionModel(), &QItemSelectionModel::currentChanged,
                     editor, &ScreenshotEditor::changeView);
    QObject::connect(model, &CollectionModel::deleted,
                     editor, &ScreenshotEditor::itemWasDeleted);

    setupToolbar();
    setup();
}

MainWindow::~MainWindow() {
    delete camera;
    delete scroller;
    delete toolbar;
    delete editor;
    delete mainLayout;
    delete editAreaLayout;
    delete centralWidget;
    delete model;
}

QSize MainWindow::sizeHint() const {
    return this->maximumSize(); //!!! currently doesnt return fullscreen size
}

void MainWindow::addScreenshot(QPixmap* img) {
    model->addImg(img);
    delete img;
}

void MainWindow::parseToolbarSignal(QAction* action) {
    QString text = action->iconText();
    if (text == DRAW) {
        emit canvasModeChanged(Canvas::penMode);
    } else if (text == ERASE) {
        emit canvasModeChanged(Canvas::eraseMode);
    } else if (text == NEW_COPY) {
        QStandardItem* item = editor->getCurrItem();
        if (item) {
            QPixmap* img;
            try {
                img = new QPixmap(item->data(Qt::UserRole).value<QPixmap>());
            } catch (_exception& e) {
                throw std::domain_error("MainWindow::ParseToolbarSignal - QVariant conversion failure");
            }
            QStandardItem* parent = model->findParent(editor->getCurrItem());
            model->addImg(img, parent);
            delete img;
        }
    } else if (text == DELETE) {
        QStandardItem* item = editor->getCurrItem();
        if (item != nullptr) {
            model->deleteImg(item);
        }
    } else if (text == NEW_SCREENSHOT) {
        camera->show();
        this->setWindowState(Qt::WindowMinimized);
    }
}

void MainWindow::setupToolbar() {
    toolbar = new QToolBar(this);
    toolbar->addAction(DRAW);
    toolbar->addAction(ERASE);
    toolbar->addSeparator();
    toolbar->addAction(SAVE_TO_FILE, editor, &ScreenshotEditor::save);
    toolbar->addAction(NEW_COPY);
    toolbar->addAction(DELETE);
    toolbar->addSeparator();
    toolbar->addAction(NEW_SCREENSHOT);

    QObject::connect(toolbar, &QToolBar::actionTriggered,
                     this, &MainWindow::parseToolbarSignal);
}

void MainWindow::setup() {
    this->setWindowState(Qt::WindowMaximized);
    this->setToolButtonStyle(Qt::ToolButtonFollowStyle);

    editAreaLayout = new QGridLayout();
    editAreaLayout->addWidget(toolbar);
    editAreaLayout->addWidget(editor);

    mainLayout->addWidget(scroller, 1);
    mainLayout->addLayout(editAreaLayout, 4);
}







