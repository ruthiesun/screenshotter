#include "screenshoteditor.h"
#include <QGridLayout>
#include <QLayout>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsEllipseItem>
#include <QSizePolicy>

ScreenshotEditor::ScreenshotEditor(QWidget* parent) : QWidget(parent) {
    currImg = nullptr;
    item = nullptr;

    scene = new QGraphicsScene();

    Setup();
}

ScreenshotEditor::ScreenshotEditor(QPixmap* img, QWidget* parent) : QWidget(parent) {
    currImg = img;
    item = new QGraphicsPixmapItem(*currImg);

    scene = new QGraphicsScene();
    scene->addItem(item);

    Setup();
}

void ScreenshotEditor::Setup() {
    viewer = new QGraphicsView(scene);
    mainLayout = new QVBoxLayout(this);
    this->layout()->addWidget(viewer);
}
