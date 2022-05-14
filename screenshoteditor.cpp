#include "screenshoteditor.h"
#include <QGridLayout>
#include <QLayout>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsEllipseItem>
#include <QSizePolicy>
#include <iostream>

ScreenshotEditor::ScreenshotEditor(QStandardItemModel* m, QWidget* parent) : QWidget(parent) {
    currImg = nullptr;
    item = nullptr;

    model = m;
    scene = new QGraphicsScene();
    mainLayout = new QVBoxLayout(this);
    viewer = new QGraphicsView(scene);
    this->layout()->addWidget(viewer);

}

void ScreenshotEditor::ChangeView(const QModelIndex &current, const QModelIndex &previous) {
    this->layout()->removeWidget(viewer);
    delete(viewer);

    currImg = model->itemFromIndex(current);

    item = new QGraphicsPixmapItem(currImg->data(Qt::DecorationRole).value<QPixmap>());

    scene = new QGraphicsScene();
    scene->addItem(item);
    viewer = new QGraphicsView(scene);
    this->layout()->addWidget(viewer);
}

QStandardItem* ScreenshotEditor::GetCurrImg() {
    return currImg;
}

void ScreenshotEditor::Setup() {


}
