#include "canvasviewer.h"
#include <QMouseEvent>


void CanvasViewer::mouseMoveEvent(QMouseEvent *mouseEvent) {
    QPoint screenPos = this->mapToScene(mouseEvent->pos()).toPoint();
    emit PaintEvent(screenPos);
}

void CanvasViewer::mousePressEvent(QMouseEvent *mouseEvent) {
    QPoint screenPos = this->mapToScene(mouseEvent->pos()).toPoint();
    emit PaintEvent(screenPos);
}
