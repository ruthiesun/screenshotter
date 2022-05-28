#include "canvas.h"
#include <QGraphicsSceneMouseEvent>
#include <iostream>
#include <QGraphicsRectItem>
#include <QPainter>

Canvas::Canvas(QPixmap* img, QObject *parent) : QGraphicsScene{parent} {
    diameter = 10;
    currMode = penMode;

    this->img = img;
    this->setSceneRect(0, 0, img->width(), img->height());
    pen = new QPen(QBrush(Qt::blue),diameter);
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

void Canvas::MouseRelease() {

}

void Canvas::MouseDown(QPoint point) {
    if (img) {
        switch(currMode)
        {
            case penMode:
            lastPoint = point;
            addLine(point.x(), point.y(), point.x(), point.y(), *pen);
            break;

            case eraseMode:
            Erase(point);
            break;
        }
    }
}

void Canvas::Draw(QPoint point) {
    this->setSceneRect(0, 0, img->width(), img->height());
    //QGraphicsEllipseItem *item = new QGraphicsEllipseItem(point.x(), point.y(), diameter, diameter);
    //item->setPen(Qt::NoPen);
    //item->setBrush(QBrush(Qt::blue));

    //item->setVisible(true);

    //addItem(item);
    addLine(lastPoint.x(), lastPoint.y(), point.x(), point.y(), *pen);
    lastPoint = point;
}

void Canvas::Erase(QPoint point) {
    //!!!
}

void Canvas::drawBackground(QPainter *painter, const QRectF &rect) {
    const QRectF bgRect = QRect(0, 0, img->width(), img->height());
    painter->setBackgroundMode(Qt::TransparentMode);
    painter->drawPixmap(bgRect, *img, bgRect);
}
