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
    mainLayout = new QVBoxLayout(this);
    viewer = new CanvasViewer();
    this->layout()->addWidget(viewer);
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

    QObject::connect(viewer, &CanvasViewer::Stroke,
                     scene, &Canvas::ParseMouse);
    QObject::connect(viewer, &CanvasViewer::DoneStroke,
                     scene, &Canvas::MouseRelease);

    //viewer->fitInView(viewer->mapToScene(img->rect()).boundingRect());//, Qt::KeepAspectRatioByExpanding);
    viewer->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    this->layout()->addWidget(viewer);
}


void ScreenshotEditor::Setup() {


}
