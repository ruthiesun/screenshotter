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
    }

    viewer->setScene(scene);
    QObject::connect(viewer, &CanvasViewer::Stroke,
                     scene, &Canvas::ParseMouse);
    QObject::connect(viewer, &CanvasViewer::DoneStroke,
                     scene, &Canvas::MouseRelease);


    viewer->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    this->layout()->addWidget(viewer);
}

//modified from https://stackoverflow.com/questions/7451183/how-to-create-image-file-from-qgraphicsscene-qgraphicsview
void ScreenshotEditor::UpdateView(QStandardItem* item) {

    scene->clearSelection();                                                  // Selections would also render to the file
/*
    QPixmap originalImg = currImg->data(Qt::UserRole).value<QPixmap>();
    QRectF itemsRect = scene->itemsBoundingRect();
    int imgWidth = originalImg.width();
    int imgHeight = originalImg.height();
    int itemsWidth = itemsRect.width();
    int itemsHeight = itemsRect.height();
    scene->setSceneRect(QRectF(0,0,std::max(imgWidth,itemsWidth), std::max(imgHeight,itemsHeight)));                          // Re-shrink the scene to it's bounding contents

*/
    QPixmap *img = new QPixmap(scene->sceneRect().size().toSize());  // Create the image with the exact size of the shrunk scene
    img->fill(Qt::blue);   //!!!!                                           // Start all pixels transparent

    QPainter painter(img);
    scene->render(&painter);
    emit ImgChanged(img, item);
}
