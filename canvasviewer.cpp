#include "canvasviewer.h"
#include <QMouseEvent>
#include <iostream>
#include <QGraphicsView>

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
    std::cout << "resize" << std::endl;
    if (scene()) {
        this->fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
    }
}

