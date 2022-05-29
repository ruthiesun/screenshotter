#ifndef CANVASVIEWER_H
#define CANVASVIEWER_H

#include <QGraphicsView>
#include "canvas.h"

/*
 * viewport for a screenshot (represented by a canvas)
 */
class CanvasViewer : public QGraphicsView {
    Q_OBJECT
public:
    using QGraphicsView::QGraphicsView;

public slots:

signals:
    void StartStroke(QPoint point);
    void Stroke(QPoint point);
    void DoneStroke();

protected:
    /*
     * EFFECTS:     signals where the mouse was pressed
     */
    void mousePressEvent(QMouseEvent *mouseEvent) override;

    /*
     * EFFECTS:     signals where the mouse was last after the move
     */
    void mouseMoveEvent(QMouseEvent *mouseEvent) override;

    /*
     * EFFECTS:     if there is a screenshot being displayed while the viewport is beign resized, scales the screenshot while keeping the aspect ratio
     */
    void resizeEvent(QResizeEvent *event) override;


private:

};

#endif // CANVASVIEWER_H
