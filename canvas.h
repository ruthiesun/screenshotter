#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsScene>
#include <QStandardItem>

/*
 * displays a screenshot in a background layer as well as the user's drawings in an upper layer
 */
class Canvas : public QGraphicsScene {
        Q_OBJECT
public:
    enum Mode { penMode, eraseMode };

    /*
     * EFFECTS:     constructor
     */
    explicit Canvas(QPixmap* img = nullptr, QObject *parent = nullptr);

    /*
     * EFFECTS:     destructor
     */
    ~Canvas();

public slots:
    /*
     * EFFECTS:     changes current mode to the given mode
     */
    void ChangeMode(Canvas::Mode mode);

    /*
     * EFFECTS:     if current mode is penMode, draws a line from previous point to given point with the pen
     *              if current mode is eraseMode, erases the top level item at the given point
     */
    void ParseMouse(QPoint point);

    /*
     * EFFECTS:     if current mode is penMode, draws a dot at the given point
     *              if current mode is eraseMode, erases the top level item at the given point
     */
    void MouseDown(QPoint point);

signals:

protected:
    /*
     * REQUIRES:    img is not null
     * EFFECTS:     sets background layer to img
     */
    void drawBackground(QPainter *painter, const QRectF &rect) override;


private:
    const QPen *pen;
    const QPixmap* img;
    qreal diameter;
    Mode currMode;
    QPoint lastPoint;

    /*
     * EFFECTS: draws a line from previous point to given point with the pen
     */
    void Draw(QPoint point);

    /*
     * EFFECTS: erases the top level item at the given point
     */
    void Erase(QPoint point);
};

#endif // CANVAS_H
