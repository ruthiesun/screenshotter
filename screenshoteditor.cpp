#include "screenshoteditor.h"
#include <QGridLayout>
#include <QLayout>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsEllipseItem>
#include <QSizePolicy>
#include <iostream>
#include <QHash>

ScreenshotEditor::ScreenshotEditor(QStandardItemModel* m, QWidget* parent) : QWidget(parent) {
    currImg = nullptr;
    model = m;
    itemToScene = new QHash<QStandardItem*,Canvas*>();
    mainLayout = new QVBoxLayout(this);
    viewer = new CanvasViewer();
    this->layout()->addWidget(viewer);
}

ScreenshotEditor::~ScreenshotEditor() {
    delete(scene);
    delete(viewer);
    delete(mainLayout);
    //free QHash and all the values (scenes) !!!
}

QStandardItem* ScreenshotEditor::GetCurrImg() {
    return currImg;
}

void ScreenshotEditor::ChangeView(const QModelIndex &current, const QModelIndex &previous) { //!!!temp implementation (does not presenve scene states between switches)
    delete(viewer);
    viewer = new CanvasViewer();
    currImg = model->itemFromIndex(current);

    if (itemToScene->contains(currImg)) {
        scene = itemToScene->value(currImg);
        viewer->setScene(scene);
    } else {
        QPixmap* img = new QPixmap(currImg->data(Qt::DecorationRole).value<QPixmap>());
        scene = new Canvas(img, this);
        itemToScene->insert(currImg, scene);
    }

    viewer->setScene(scene);
    QObject::connect(viewer, &CanvasViewer::Stroke,
                     scene, &Canvas::ParseMouse);
    QObject::connect(viewer, &CanvasViewer::DoneStroke,
                     scene, &Canvas::MouseRelease);

    viewer->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    this->layout()->addWidget(viewer);


    //https://stackoverflow.com/questions/7451183/how-to-create-image-file-from-qgraphicsscene-qgraphicsview !!! todo

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

