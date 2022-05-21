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
    //item = nullptr;

    model = m;
    scene = new Canvas();
    mainLayout = new QVBoxLayout(this);
    viewer = new CanvasViewer(scene);
    //viewer = new QGraphicsView(scene);
    this->layout()->addWidget(viewer);

    QObject::connect(viewer, &CanvasViewer::PaintEvent, //!!!
                     scene, &Canvas::AddDrawing);
}

QStandardItem* ScreenshotEditor::GetCurrImg() {
    return currImg;
}

void ScreenshotEditor::ChangeView(const QModelIndex &current, const QModelIndex &previous) {
    this->layout()->removeWidget(viewer);
    delete(viewer);

    currImg = model->itemFromIndex(current);
    QPixmap* img = new QPixmap(currImg->data(Qt::DecorationRole).value<QPixmap>());

    scene = new Canvas(img, this);
    viewer = new CanvasViewer(scene);

    QObject::connect(viewer, &CanvasViewer::PaintEvent, //!!!
                     scene, &Canvas::AddDrawing);

    this->layout()->addWidget(viewer);
}


void ScreenshotEditor::Setup() {


}
