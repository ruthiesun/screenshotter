#include "screenshoteditor.h"
#include "collectionmodel.h"
#include <QVBoxLayout>
#include <QHash>
#include <QFile>
#include "mainwindow.h"
#include <iostream>
#include <QFileDialog>
#include <QClipboard>
#include <QApplication>
#include <QMimeData>

ScreenshotEditor::ScreenshotEditor(CollectionModel* m, QWidget* parent) : QWidget(parent) {
    currImgItem = nullptr;
    model = m;
    itemToScene = new QHash<QStandardItem*,Canvas*>();
    mainLayout = new QVBoxLayout(this);
    viewer = new CanvasViewer();

    this->layout()->addWidget(viewer);

    QObject::connect(this, &ScreenshotEditor::imgModified,
                     model, &CollectionModel::changeDecoration);

}

ScreenshotEditor::~ScreenshotEditor() {
    delete viewer;
    delete mainLayout;
    for (Canvas* scene : itemToScene->values()) {
        delete scene;
    }
    delete itemToScene;
}

QStandardItem* ScreenshotEditor::getCurrItem() {
    return currImgItem;
}


void ScreenshotEditor::toClipboard() {
    if (currImgItem) {
        saver.imgToClipboard(getCurrScreenImg());
    }
}

void ScreenshotEditor::itemWasDeleted(QStandardItem* item) {
    if (itemToScene->contains(item)) {
        delete itemToScene->take(item);
        currImgItem = nullptr;
    }
}

void ScreenshotEditor::changeView(const QModelIndex &current, const QModelIndex &previous) {
    viewer->setScene(nullptr);
    if (current.isValid()) {
        viewer->disconnect();
        viewer->setScene(nullptr);
        currImgItem = model->itemFromIndex(current);
        emit changingToParentItem(currImgItem, model->findParent(currImgItem)); //!!! just emit with currImgItem once disjoint set implemented in colourselector

        if (itemToScene->contains(currImgItem)) {
            scene = itemToScene->value(currImgItem);
        } else {
            QPixmap* img = new QPixmap(currImgItem->data(Qt::UserRole).value<QPixmap>()); //dealloced with Canvas destructor
            scene = new Canvas(img, this);
            itemToScene->insert(currImgItem, scene);
            QObject::connect((MainWindow*) this->nativeParentWidget(), &MainWindow::canvasModeChanged,
                             scene, &Canvas::changeMode);
            QObject::connect(scene, &Canvas::changed,
                             this, &ScreenshotEditor::imgRegionsChanged);
        }

        viewer->setScene(scene);
        QObject::connect(viewer, &CanvasViewer::stroke,
                         scene, &Canvas::mouseDrag);
        QObject::connect(viewer, &CanvasViewer::startStroke,
                         scene, &Canvas::mouseDown);

        currImg = *getCurrScreenImg();
    }
}

void ScreenshotEditor::imgRegionsChanged(const QList<QRectF> &region) {
    for (QRectF modifiedArea : region) {
        QPainter painter(&currImg);
        scene->render(&painter, modifiedArea, modifiedArea);
    }
    signalImgModified(&currImg);
}

void ScreenshotEditor::changePenColour(QColor c) {
    if (currImgItem) {
        scene->setPenColour(c);
    }
}

void ScreenshotEditor::signalImgModified(QPixmap* img) {
    emit imgModified(img, currImgItem);
}

void ScreenshotEditor::save() {
    if (currImgItem) {
        saver.saveImg(getCurrScreenImg());
    }
}

QPixmap* ScreenshotEditor::getCurrScreenImg() {
    return saver.getCanvasAsPixmap(scene);
}
