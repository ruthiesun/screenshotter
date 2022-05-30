#include "screenshoteditor.h"
#include "collectionmodel.h"
#include <QVBoxLayout>
#include <QHash>
#include <QFile>
#include "mainwindow.h"
#include <iostream>
#include <QFileDialog>


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
    delete viewer;
    delete mainLayout;
    for (Canvas* scene : itemToScene->values()) {
        delete scene;
    }
    delete itemToScene;
}

QStandardItem* ScreenshotEditor::GetCurrImg() {
    return currImg;
}

void ScreenshotEditor::DeletedItem(QStandardItem* item) {
    if (itemToScene->contains(item)) {
        delete itemToScene->take(item);
        currImg = nullptr;
    }
}

void ScreenshotEditor::ChangeView(const QModelIndex &current, const QModelIndex &previous) {
    if (currImg) {
        UpdateView(model->itemFromIndex(previous));
    }
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
            QObject::connect((MainWindow*) this->nativeParentWidget(), &MainWindow::CanvasModeChanged,
                             scene, &Canvas::ChangeMode);
        }

        viewer->setScene(scene);
        QObject::connect(viewer, &CanvasViewer::Stroke,
                         scene, &Canvas::ParseMouse);
        QObject::connect(viewer, &CanvasViewer::StartStroke,
                         scene, &Canvas::MouseDown);

        this->layout()->addWidget(viewer);
    }
}

void ScreenshotEditor::UpdateView(QStandardItem* item) {
    QPixmap* img = GetCurrScreenImg();
    emit ImgChanged(img, item);
    delete img;
}

void ScreenshotEditor::Save() {
    if (currImg) {
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                   "/home/BeautifulNewScreenshot.png",
                                   tr("Images (*.png *.bmp *.jpg *.jpeg"));

        QFile file(fileName);
        QPixmap* img = GetCurrScreenImg();
        file.open(QIODevice::WriteOnly);
        if (!img->save(&file)) {
            throw std::domain_error("ScreenshotEditor::UpdateView - failed to save image");
        }
        file.close();
        delete img;
    }
}

QPixmap* ScreenshotEditor::GetCurrScreenImg() {
    scene->clearSelection();
    QPixmap *img = new QPixmap(scene->sceneRect().size().toSize());
    QPainter painter(img);
    scene->render(&painter, img->rect(), img->rect());
    return img;
}
