#include "screenshoteditor.h"
#include <QGridLayout>
#include <QLayout>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsEllipseItem>
#include <QSizePolicy>

ScreenshotEditor::ScreenshotEditor(QStandardItemModel* m, QWidget* parent) : QWidget(parent) {
    currImg = nullptr;
    item = nullptr;

    model = m;
    scene = new QGraphicsScene();

    Setup();
}

void ScreenshotEditor::ChangeView(const QModelIndex &current, const QModelIndex &previous) {
    if (currImg) {
        delete(currImg);
        delete(scene);
        delete(viewer);
        delete(mainLayout);
    }
    currImg = model->itemFromIndex(current);
    item = new QGraphicsPixmapItem(*currImg->data(Qt::UserRole).value<QPixmap*>());

    scene = new QGraphicsScene();
    scene->addItem(item);

    Setup();
}

QStandardItem* ScreenshotEditor::GetCurrImg() {
    return currImg;
}

void ScreenshotEditor::Setup() {
    viewer = new QGraphicsView(scene);
    mainLayout = new QVBoxLayout(this);
    this->layout()->addWidget(viewer);
}
