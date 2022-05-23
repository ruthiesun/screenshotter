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
    model = m;
    itemToView = new QHash<QStandardItem*,CanvasViewer*>();
    mainLayout = new QVBoxLayout(this);
    viewer = new CanvasViewer();
    this->layout()->addWidget(viewer);
}

ScreenshotEditor::~ScreenshotEditor() {
    delete(scene);
    delete(viewer);
    delete(mainLayout);
}

QStandardItem* ScreenshotEditor::GetCurrImg() {
    return currImg;
}

void ScreenshotEditor::ChangeView(const QModelIndex &current, const QModelIndex &previous) { //!!!temp implementation (does not presenve scene states between switches)

    this->layout()->removeWidget(viewer);
    currImg = model->itemFromIndex(current);
    if (itemToView->contains(currImg)) {
        viewer = itemToView->value(currImg);

        viewer->scene()->update();
        viewer->update();
    } else {

        currImg = model->itemFromIndex(current);
        QPixmap* img = new QPixmap(currImg->data(Qt::DecorationRole).value<QPixmap>());

        scene = new Canvas(img, this);
        viewer = new CanvasViewer(scene);

        QObject::connect(viewer, &CanvasViewer::Stroke,
                         scene, &Canvas::ParseMouse);
        QObject::connect(viewer, &CanvasViewer::DoneStroke,
                         scene, &Canvas::MouseRelease);

        viewer->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);

        itemToView->insert(currImg, viewer);

    }
    this->layout()->addWidget(viewer);


    //---------
/*
    this->layout()->removeWidget(viewer);
    delete(viewer);

    currImg = model->itemFromIndex(current);
    QPixmap* img = new QPixmap(currImg->data(Qt::DecorationRole).value<QPixmap>());

    scene = new Canvas(img, this);
    viewer = new CanvasViewer(scene);

    QObject::connect(viewer, &CanvasViewer::Stroke,
                     scene, &Canvas::ParseMouse);
    QObject::connect(viewer, &CanvasViewer::DoneStroke,
                     scene, &Canvas::MouseRelease);

    viewer->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    this->layout()->addWidget(viewer);
    */
}

