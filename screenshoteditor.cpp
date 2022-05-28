#include "screenshoteditor.h"
#include "collectionmodel.h"
#include <QGridLayout>
#include <QLayout>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsEllipseItem>
#include <QSizePolicy>
#include <iostream>
#include <QHash>
#include <QFile>
#include <QSizePolicy>
#include "mainwindow.h"


ScreenshotEditor::ScreenshotEditor(CollectionModel* m, QWidget* parent) : QWidget(parent) {
    currImg = nullptr;
    model = m;
    itemToScene = new QHash<QStandardItem*,Canvas*>();
    mainLayout = new QVBoxLayout(this);
    viewer = new CanvasViewer();
    this->layout()->addWidget(viewer);

    QObject::connect(this, &ScreenshotEditor::ImgChanged,
                     model, &CollectionModel::ChangeDecoration);

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

void ScreenshotEditor::ChangeView(const QModelIndex &current, const QModelIndex &previous) {
    if (currImg) {
        UpdateView(model->itemFromIndex(previous));
    }

    delete(viewer);
    viewer = new CanvasViewer();
    currImg = model->itemFromIndex(current);

    if (itemToScene->contains(currImg)) {
        scene = itemToScene->value(currImg);
        viewer->setScene(scene);
    } else {
        QPixmap* img = new QPixmap(currImg->data(Qt::UserRole).value<QPixmap>());
        scene = new Canvas(img, this);
        itemToScene->insert(currImg, scene);
        QObject::connect((MainWindow*) this->nativeParentWidget(), &MainWindow::CanvasModeChanged,
                         scene, &Canvas::ChangeMode);
    }

    viewer->setScene(scene);
    QObject::connect(viewer, &CanvasViewer::Stroke,
                     scene, &Canvas::ParseMouse);
    QObject::connect(viewer, &CanvasViewer::StartStroke,
                     scene, &Canvas::MouseDown);
    QObject::connect(viewer, &CanvasViewer::DoneStroke,
                     scene, &Canvas::MouseRelease);

    this->layout()->addWidget(viewer);
}

void ScreenshotEditor::UpdateView(QStandardItem* item) {
    QPixmap* img = GetCurrScreenImg();
    emit ImgChanged(img, item);
    delete(img);
}

void ScreenshotEditor::Save() {
    if (currImg) {
        QFile file("test.png");
        QPixmap* img = GetCurrScreenImg();
        file.open(QIODevice::WriteOnly);
        if (!img->save(&file, "PNG")) {
            throw std::domain_error("ScreenshotEditor::UpdateView - failed to save image");
        }
        file.close();
        delete(img);
    }
}

QPixmap* ScreenshotEditor::GetCurrScreenImg() {
    scene->clearSelection();
    QPixmap *img = new QPixmap(scene->sceneRect().size().toSize());
    QPainter painter(img);
    scene->render(&painter, img->rect(), img->rect());
    return img;
}
