#include "canvasviewer.h"
#include <QMouseEvent>
#include <QGraphicsView>

void CanvasViewer::mouseMoveEvent(QMouseEvent *mouseEvent) {
    QPoint screenPos = this->mapToScene(mouseEvent->pos()).toPoint();
    emit Stroke(screenPos);
}

void CanvasViewer::mousePressEvent(QMouseEvent *mouseEvent) {
    QPoint screenPos = this->mapToScene(mouseEvent->pos()).toPoint();
    emit StartStroke(screenPos);
}

void CanvasViewer::resizeEvent(QResizeEvent *event) {
    if (scene()) {
        this->fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
    }
}

