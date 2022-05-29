#include "canvas.h"
#include <QPainter>
#include <QGraphicsItem>
#include <iostream>

Canvas::Canvas(QPixmap* img, QObject *parent) : QGraphicsScene{parent} {
    diameter = 5;
    currMode = penMode;

    this->img = img;
    this->setSceneRect(0, 0, img->width(), img->height());
    pen = QPen(QBrush(Qt::blue),diameter,Qt::SolidLine,Qt::RoundCap);
}

Canvas::~Canvas() {
    delete img;
}

void Canvas::ChangeMode(Canvas::Mode mode) {
    currMode = mode;
}

void Canvas::ParseMouse(QPoint point) {
    if (img) {
        switch(currMode)
        {
            case penMode:
            Draw(point);
            break;

            case eraseMode:
            Erase(point);
            break;
        }
    }
}

void Canvas::MouseDown(QPoint point) {
    if (img) {
        switch(currMode)
        {
            case penMode:
            lastPoint = point;
            addEllipse(point.x()-diameter/2, point.y()-diameter/2, diameter, diameter, pen);
            break;

            case eraseMode:
            Erase(point);
            break;
        }
    }
}

void Canvas::drawBackground(QPainter *painter, const QRectF &rect) {
    const QRectF bgRect = QRect(0, 0, img->width(), img->height());
    painter->drawPixmap(bgRect, *img, bgRect);
}

void Canvas::Draw(QPoint point) {
    this->setSceneRect(0, 0, img->width(), img->height());
    addLine(lastPoint.x(), lastPoint.y(), point.x(), point.y(), pen);
    lastPoint = point;
}

void Canvas::Erase(QPoint point) {
    QGraphicsItem* item = itemAt(point, QTransform());
    if (item) {
        removeItem(item);
        delete(item);
    }
}


