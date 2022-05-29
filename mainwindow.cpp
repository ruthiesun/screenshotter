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
    QObject::connect(camera, &Camera::Snapped,
                     this, &MainWindow::AddScreenshot);

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    mainLayout = new QHBoxLayout(centralWidget);

    scroller = new CollectionViewer(model, this);
    editor = new ScreenshotEditor(model, this);
    QObject::connect(scroller->selectionModel(), &QItemSelectionModel::currentChanged,
                     editor, &ScreenshotEditor::ChangeView);
    QObject::connect(model, &CollectionModel::Cleared,
                     editor, &ScreenshotEditor::DeletedItem);

    SetupToolbar();
    Setup();
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

QSize MainWindow::sizeHint() const {
    return this->maximumSize(); //!!! currently doesnt return fullscreen size
}

void MainWindow::AddScreenshot(QPixmap* img) {
    model->Add(img);
    delete(img);
}

void MainWindow::ParseToolbarSignal(QAction* action) {
    QString text = action->iconText();
    if (text == DRAW) {
        emit CanvasModeChanged(Canvas::penMode);
    } else if (text == ERASE) {
        emit CanvasModeChanged(Canvas::eraseMode);
    } else if (text == NEW_COPY) {
        QPixmap* img;
        try {
            img = new QPixmap(editor->GetCurrImg()->data(Qt::UserRole).value<QPixmap>());
        } catch (_exception& e) {
            throw std::domain_error("MainWindow::ParseToolbarSignal - QVariant conversion failure");
        }
        QStandardItem* parent = model->FindParent(editor->GetCurrImg());
        model->Add(img, parent);
    } else if (text == DELETE) {
        QStandardItem* item = editor->GetCurrImg();
        if (item != nullptr) {
            model->Delete(item);
        }
    } else if (text == NEW_SCREENSHOT) {
        camera->show();
        this->setWindowState(Qt::WindowMinimized);
    }
}

void MainWindow::SetupToolbar() {
    toolbar = new QToolBar(this);
    toolbar->addAction(DRAW);
    toolbar->addAction(ERASE);
    toolbar->addSeparator();
    toolbar->addAction(SAVE_TO_FILE, editor, &ScreenshotEditor::Save);
    toolbar->addAction(NEW_COPY);
    toolbar->addAction(DELETE);
    toolbar->addSeparator();
    toolbar->addAction(NEW_SCREENSHOT);

    QObject::connect(toolbar, &QToolBar::actionTriggered,
                     this, &MainWindow::ParseToolbarSignal);
}

void MainWindow::Setup() {
    this->setWindowState(Qt::WindowMaximized);
    this->setToolButtonStyle(Qt::ToolButtonFollowStyle);

    editAreaLayout = new QGridLayout();
    editAreaLayout->addWidget(toolbar);
    editAreaLayout->addWidget(editor);

    mainLayout->addWidget(scroller, 1);
    mainLayout->addLayout(editAreaLayout, 4);
}







