#include "canvas.h"
#include <QGraphicsSceneMouseEvent>
#include <iostream>
#include <QGraphicsRectItem>
#include <QPainter>

Canvas::Canvas(QObject *parent)
    : QGraphicsScene{parent}
{
    /*brush = new QBrush(Qt::SolidPattern);
    pen = QPen(*brush, 0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    brushDiameter = 15;

    mouseButtonDown = false;
    */
    diameter = 5;
    //pen = QPen();

    mouseButtonDown = false;

    this->img = new QPixmap();
}

Canvas::Canvas(QPixmap* img, QObject *parent)
    : QGraphicsScene{parent}
{
    //painter - new QPainter;
    //painter->setPen(Qt::NoPen);
    //brush = new QBrush(Qt::SolidPattern);

    diameter = 5;
    //pen = QPen(diameter);

    mouseButtonDown = false;

    this->img = img;
}

void Canvas::AddDrawing(QPoint point) {
    addEllipse(point.x(), point.y(), diameter, diameter);
}

void Canvas::DrawDot(const QPointF point) {
    std::cout << point.x() << std::endl;
    std::cout << point.y() << std::endl;
    //QGraphicsEllipseItem* dot = this->addEllipse(QRectF(point.x(), point.y(), diameter, diameter), *pen, this->foregroundBrush());
    //dot->setBrush(Qt::red);
    //QGraphicsItem* dot = ;
    std::cout << "added rect" << std::endl;
}

void Canvas::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    /*
    QPoint prev = mouseEvent->lastScreenPos();
    QPoint curr = mouseEvent->screenPos();
    addLine(prev.x(), prev.y(), curr.x(), curr.y());
    */
}

//https://forum.qt.io/topic/6313/qgraphicsview-with-qpixmap-background/4
void Canvas::drawBackground(QPainter *painter, const QRectF &rect) {
    const QRectF bgRect = QRect(0, 0, img->width(), img->height());
    painter->drawPixmap(rect, *img, bgRect);
}
