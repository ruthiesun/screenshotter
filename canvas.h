#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsScene>

/*
 * scene that displays a screenshot
 */
class Canvas : public QGraphicsScene {
        Q_OBJECT
public:
    /*
     * EFFECTS: initializes the screenshot to display to img
     */
    explicit Canvas(QPixmap* img, QObject *parent = nullptr);

public slots:
    /*
     * EFFECTS: executes modification to the screenshot at given the point based on the current mode
     */
    void ParseMouse(QPoint point);

    /*
     * !!!
     */
    void MouseRelease();

signals:


protected:
    /*
     * EFFECTS: sets background to the screenshot at hand
     */
    void drawBackground(QPainter *painter, const QRectF &rect) override;

private:
    const QPen pen;
    qreal diameter;
    const QPixmap* img;
    enum Mode { penMode, eraseMode };
    Mode currMode;

    /*
     * EFFECTS: draws a dot at the given point
     */
    void Draw(QPoint point);

    /*
     * EFFECTS: if there is an item at the given point or within the radius of the eraser, erases it
     */
    void Erase(QPoint point);
};

#endif // CANVAS_H
