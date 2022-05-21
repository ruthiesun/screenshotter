#ifndef CANVASVIEWER_H
#define CANVASVIEWER_H

#include <QGraphicsView>

class CanvasViewer : public QGraphicsView
{
    Q_OBJECT
public:
    using QGraphicsView::QGraphicsView;

public slots:

signals:
    void PaintEvent(QPoint point);

protected:
    void mousePressEvent(QMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QMouseEvent *mouseEvent) override;
};

#endif // CANVASVIEWER_H
