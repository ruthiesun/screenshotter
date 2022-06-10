#include "saver.h"
#include <QPainter>
#include <QFileDialog>
#include <QApplication>
#include <QMimeData>
#include <QClipboard>

Saver::Saver(QObject *parent) : QObject{parent} {
    clipboard = QApplication::clipboard();
}

void Saver::imgToClipboard(QPixmap* img) {
    clipboard->clear();
    QMimeData* data = new QMimeData();
    data->setImageData(*img);
    clipboard->setMimeData(data);
    delete img;
}

void Saver::saveImg(QPixmap* img) {
    QString fileName = QFileDialog::getSaveFileName(nullptr, tr("Save File"),
                               "/home/BeautifulNewScreenshot.png",
                               tr("Images (*.png *.bmp *.jpg *.jpeg"));
    if (fileName.isEmpty()) {
        return;
    }
    QFile file(fileName);

    file.open(QIODevice::WriteOnly);
    if (!img->save(&file)) {
        throw std::domain_error("Saver::saveImg - failed to save image");
    }
    file.close();
    delete img;
}

QPixmap* Saver::getCanvasAsPixmap(Canvas* canvas) {
    canvas->clearSelection();
    QRectF itemsRect = canvas->itemsBoundingRect();
    QRectF originalRect = canvas->sceneRect();

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
    canvas->render(&painter, img->rect(), newRect);
    return img;
}
