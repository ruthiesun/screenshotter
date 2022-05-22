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
    void Stroke(QPoint point);
    void DoneStroke();

protected:
    void mousePressEvent(QMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QMouseEvent *mouseEvent) override;
    void resizeEvent(QResizeEvent *event) override;
};

#endif // CANVASVIEWER_H
