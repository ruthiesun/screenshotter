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
    currImg = nullptr;
    model = m;
    itemToScene = new QHash<QStandardItem*,Canvas*>();
    mainLayout = new QVBoxLayout(this);
    viewer = new CanvasViewer();
    clipboard = QApplication::clipboard();
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
    return currImg;
}


void ScreenshotEditor::toClipboard() {
    if (currImg) {
        clipboard->clear();
        QPixmap* img = getCurrScreenImg();
        QMimeData* data = new QMimeData();
        data->setImageData(*img);
        clipboard->setMimeData(data);
        delete img;
    }
}

void ScreenshotEditor::itemWasDeleted(QStandardItem* item) {
    if (itemToScene->contains(item)) {
        delete itemToScene->take(item);
        currImg = nullptr;
    }
}

void ScreenshotEditor::changeView(const QModelIndex &current, const QModelIndex &previous) {
    if (!current.isValid()) {
        viewer->setScene(nullptr);
    } else {
        delete viewer;
        viewer = new CanvasViewer();
        currImg = model->itemFromIndex(current);

        if (itemToScene->contains(currImg)) {
            scene = itemToScene->value(currImg);
            viewer->setScene(scene);
        } else {
            QPixmap* img = new QPixmap(currImg->data(Qt::UserRole).value<QPixmap>()); //dealloced with Canvas destructor
            scene = new Canvas(img, this);
            itemToScene->insert(currImg, scene);
            QObject::connect((MainWindow*) this->nativeParentWidget(), &MainWindow::canvasModeChanged,
                             scene, &Canvas::changeMode);
            QObject::connect(scene, &Canvas::changed,
                             this, &ScreenshotEditor::imgChanged);
        }

        viewer->setScene(scene);
        QObject::connect(viewer, &CanvasViewer::stroke,
                         scene, &Canvas::mouseDrag);
        QObject::connect(viewer, &CanvasViewer::startStroke,
                         scene, &Canvas::mouseDown);

        this->layout()->addWidget(viewer);
    }
}

void ScreenshotEditor::imgChanged(const QList<QRectF> &region) {
    QPixmap* img = getCurrScreenImg();
    signalImgModified(img);
    delete img;
}

void ScreenshotEditor::signalImgModified(QPixmap* img) {
    emit imgModified(img, currImg);
}

void ScreenshotEditor::save() {
    if (currImg) {
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                   "/home/BeautifulNewScreenshot.png",
                                   tr("Images (*.png *.bmp *.jpg *.jpeg"));
        if (fileName.isEmpty()) {
            return;
        }
        QFile file(fileName);
        QPixmap* img = getCurrScreenImg();
        file.open(QIODevice::WriteOnly);
        if (!img->save(&file)) {
            throw std::domain_error("ScreenshotEditor::UpdateView - failed to save image");
        }
        file.close();
        delete img;
    }
}

QPixmap* ScreenshotEditor::getCurrScreenImg() {
    scene->clearSelection();
    QRectF itemsRect = scene->itemsBoundingRect();
    QRectF originalRect = scene->sceneRect();

    int newTopLeftX = std::min(itemsRect.topLeft().x(), originalRect.topLeft().x());
    int newTopLeftY = std::min(itemsRect.topLeft().y(), originalRect.topLeft().y());
    int newBotRightX = std::max(itemsRect.bottomRight().x(), originalRect.bottomRight().x());
    int newBotRightY = std::max(itemsRect.bottomRight().y(), originalRect.bottomRight().y());
    QPoint newTopLeft = QPoint(newTopLeftX, newTopLeftY);
    QPoint newBotRight = QPoint(newBotRightX, newBotRightY);
    QRect newRect = QRect(newTopLeft, newBotRight);

    QPixmap *img = new QPixmap(QSize(newBotRightX-newTopLeftX, newBotRightY-newTopLeftY));
    img->fill(Qt::transparent);
    QPainter painter(img);
    scene->render(&painter, img->rect(), newRect);
    return img;
}
