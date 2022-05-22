#include "canvasviewer.h"
#include <QMouseEvent>


void CanvasViewer::mouseMoveEvent(QMouseEvent *mouseEvent) {
    QPoint screenPos = this->mapToScene(mouseEvent->pos()).toPoint();
    emit Stroke(screenPos);
}

void CanvasViewer::mousePressEvent(QMouseEvent *mouseEvent) {
    QPoint screenPos = this->mapToScene(mouseEvent->pos()).toPoint();
    emit Stroke(screenPos);
}

void CanvasViewer::mouseReleaseEvent(QMouseEvent *mouseEvent) {
    emit DoneStroke();
}

void CanvasViewer::resizeEvent(QResizeEvent *event) {
    //!!!
}

