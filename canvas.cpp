#include "canvas.h"
#include <QGraphicsSceneMouseEvent>
#include <iostream>
#include <QGraphicsRectItem>
#include <QPainter>

Canvas::Canvas(QObject *parent)
    : QGraphicsScene{parent}
{
    diameter = 5;

    mouseButtonDown = false;

    this->img = new QPixmap();
}

Canvas::Canvas(QPixmap* img, QObject *parent)
    : QGraphicsScene{parent}
{
    diameter = 5;

    mouseButtonDown = false;

    this->img = img;
    this->setSceneRect(0, 0, img->width(), img->height());
}

void Canvas::AddDrawing(QPoint point) {
    this->setSceneRect(0, 0, img->width(), img->height());
    //QGraphicsEllipseItem *item = new QGraphicsEllipseItem(point.x(), point.y(), diameter, diameter);
    QPixmap square = QPixmap(5,5);
    square.fill(Qt::blue);
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(square);
    //addEllipse(point.x(), point.y(), diameter, diameter);
    //addItem(item);
    item->setPos(point.x(), point.y());
    item->setVisible(true);
    item->setEnabled(false);
    addItem(item);
}


//https://forum.qt.io/topic/6313/qgraphicsview-with-qpixmap-background/4
void Canvas::drawBackground(QPainter *painter, const QRectF &rect) {
    const QRectF bgRect = QRect(0, 0, img->width(), img->height());
    painter->drawPixmap(bgRect, *img, bgRect);
}
