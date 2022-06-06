#include "canvas.h"
#include <QPainter>
#include <QGraphicsItem>
#include <iostream>
#include "paletteretriever.h"

Canvas::Canvas(QPixmap* img, QObject *parent) : QGraphicsScene{parent} {
    PaletteRetriever *p = new PaletteRetriever(img);
    p->generatePalette();
    diameter = 5;
    currMode = penMode;

    this->img = img;
    this->setSceneRect(0, 0, img->width(), img->height());
    pen = QPen(QBrush(Qt::blue),diameter,Qt::SolidLine,Qt::RoundCap);
}

Canvas::~Canvas() {
    delete img;
}

void Canvas::changeMode(Canvas::Mode mode) {
    currMode = mode;
}

void Canvas::mouseDrag(QPoint point) {
    if (img) {
        switch(currMode)
        {
            case penMode:
            draw(point);
            break;

            case eraseMode:
            erase(point);
            break;
        }
    }
}

void Canvas::mouseDown(QPoint point) {
    if (img) {
        switch(currMode)
        {
            case penMode:
            lastPoint = point;
            addLine(lastPoint.x(), lastPoint.y(), point.x()-0.1, point.y()-0.1, pen);
            break;

            case eraseMode:
            erase(point);
            break;
        }
    }
}

void Canvas::drawBackground(QPainter *painter, const QRectF &rect) {
    const QRectF bgRect = QRect(0, 0, img->width(), img->height());
    painter->drawPixmap(bgRect, *img, bgRect);
}

void Canvas::draw(QPoint point) {
    this->setSceneRect(0, 0, img->width(), img->height());
    addLine(lastPoint.x(), lastPoint.y(), point.x(), point.y(), pen);
    lastPoint = point;
}

void Canvas::erase(QPoint point) {
    QRectF eraserArea = QRectF(QPointF(point.x()-diameter, point.y()-diameter), QPointF(point.x()+diameter, point.y()+diameter));
    QList<QGraphicsItem*> itemsToErase = items(eraserArea);
    for (QGraphicsItem *item : itemsToErase) {
        removeItem(item);
        delete item;
    }
}


