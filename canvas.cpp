#include "canvas.h"
#include <QGraphicsSceneMouseEvent>
#include <iostream>
#include <QGraphicsRectItem>
#include <QPainter>

Canvas::Canvas(QObject *parent)
    : QGraphicsScene{parent}
{
    Setup();

    this->img = nullptr;
}

Canvas::Canvas(QPixmap* img, QObject *parent)
    : QGraphicsScene{parent}
{
    Setup();

    this->img = img;
    this->setSceneRect(0, 0, img->width(), img->height());
}

void Canvas::ParseMouse(QPoint point) {
    if (img) {
        switch(currMode)
        {
            case penMode: Draw(point); break;
            case eraseMode: Erase(point); break;
        }
    }


}

void Canvas::MouseRelease() {
    //!!!
}

void Canvas::Draw(QPoint point) {
    this->setSceneRect(0, 0, img->width(), img->height());
    QGraphicsEllipseItem *item = new QGraphicsEllipseItem(point.x(), point.y(), diameter, diameter);
    item->setPen(Qt::NoPen);
    item->setBrush(QBrush(Qt::blue));

    item->setVisible(true);

    addItem(item);
}

void Canvas::Erase(QPoint point) {
    //!!!
}

void Canvas::Setup() {
    diameter = 10;
    currMode = penMode;
}

void Canvas::drawBackground(QPainter *painter, const QRectF &rect) {
    const QRectF bgRect = QRect(0, 0, img->width(), img->height());
    painter->drawPixmap(rect, *img, bgRect);
}