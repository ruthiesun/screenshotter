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


    //viewer->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    //viewer->setFixedHeight(scene->sceneRect().height());
    //viewer->setFixedHeight(scene->sceneRect().width());
    //viewer->setSizePolicy(QSizePolicy::Fixed);

    //TEMP from https://www.bogotobogo.com/Qt/Qt5_QGraphicsView_animation.php
    this->layout()->addWidget(viewer);

    QLineF topLine(scene->sceneRect().topLeft(),
                       scene->sceneRect().topRight());
        QLineF leftLine(scene->sceneRect().topLeft(),
                       scene->sceneRect().bottomLeft());
        QLineF rightLine(scene->sceneRect().topRight(),
                       scene->sceneRect().bottomRight());
        QLineF bottomLine(scene->sceneRect().bottomLeft(),
                       scene->sceneRect().bottomRight());

        QPen myPen = QPen(Qt::red);

        scene->addLine(topLine, myPen);
        scene->addLine(leftLine, myPen);
        scene->addLine(rightLine, myPen);
        scene->addLine(bottomLine, myPen);
        //END TEMP
}

//modified from https://stackoverflow.com/questions/7451183/how-to-create-image-file-from-qgraphicsscene-qgraphicsview
void ScreenshotEditor::UpdateView(QStandardItem* item) {
    scene->clearSelection();
    QPixmap *img = new QPixmap(scene->sceneRect().size().toSize());
    QPainter painter(img);
    scene->render(&painter, img->rect(), img->rect());
    emit ImgChanged(img, item);
    QFile file("test.png");
    file.open(QIODevice::WriteOnly);
    if (img->save(&file, "PNG")) {
        std::cout << "saved test img" << std::endl;
    }
    file.close();
}
