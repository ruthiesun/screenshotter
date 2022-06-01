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
#include <QSizePolicy>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    model = new CollectionModel(this);
    camera = new Camera();
    camera->setAttribute(Qt::WA_QuitOnClose, false);
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
    scroller->initDelegate();
}

MainWindow::~MainWindow() {
    delete camera;
    delete scroller;
    delete toolbar;
    delete editor;
    delete editAreaLayout;
    delete mainLayout;
    delete centralWidget;
    delete model;
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
        if (camera->getPrevPos()) {
            camera->move(*camera->getPrevPos());
        }
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
    this->setToolButtonStyle(Qt::ToolButtonFollowStyle);

    editAreaLayout = new QGridLayout();
    editAreaLayout->addWidget(toolbar);
    editAreaLayout->addWidget(editor);

    mainLayout->addWidget(scroller, scrollerRatioValue);
    mainLayout->addLayout(editAreaLayout, editorRatioValue);
}
/*
//https://www.qtcentre.org/threads/59667-QMainWindow-Minimize
void MainWindow::changeEvent(QEvent *event)
{
    QMainWindow::changeEvent(event);
    if( event->type() == QEvent::WindowStateChange )
    {
        if( windowState() == Qt::WindowMaximized )
        {
            this->setWindowState(Qt::WindowMaximized);
        }
    }
}
*/

QSize MainWindow::sizeHint() const {
    //return this->maximumSize(); //!!! currently doesnt return fullscreen size
    return QGuiApplication::primaryScreen()->size();
}






