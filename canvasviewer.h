#ifndef CANVASVIEWER_H
#define CANVASVIEWER_H

#include <QGraphicsView>
#include "canvas.h"

/*
 * viewport for a screenshot
 */
class CanvasViewer : public QGraphicsView {
    Q_OBJECT
public:
    using QGraphicsView::QGraphicsView;

public slots:

signals:
    void Stroke(QPoint point);
    void DoneStroke();

protected:
    /*
     * EFFECTS: signals to the scene where the mouse was pressed
     */
    void mousePressEvent(QMouseEvent *mouseEvent) override;

    /*
     * EFFECTS: signals to the scene that the mouse was released
     */
    void mouseReleaseEvent(QMouseEvent *mouseEvent) override;

    /*
     * EFFECTS: signals to the scene where the mouse was last after the move
     */
    void mouseMoveEvent(QMouseEvent *mouseEvent) override;

    /*
     * !!!
     */
    void resizeEvent(QResizeEvent *event) override;

private:

};



#endif // CANVASVIEWER_H
