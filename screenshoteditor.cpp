#include "screenshoteditor.h"
#include <QGridLayout>
#include <QLayout>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsEllipseItem>
#include <QSizePolicy>

ScreenshotEditor::ScreenshotEditor(QPixmap* img, QWidget* parent) : QWidget(parent) {
    currImg = img;

    Setup();
    this->setBackgroundRole(QPalette::Dark);

    mainLayout = new QVBoxLayout(this);
    this->layout()->addWidget(viewer);
}

void ScreenshotEditor::Setup() {

    item = new QGraphicsPixmapItem(*currImg);
    scene = new QGraphicsScene();
    scene->addItem(item);

    viewer = new QGraphicsView(scene);

}
