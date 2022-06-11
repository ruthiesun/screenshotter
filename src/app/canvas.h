#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsScene>
#include <QStandardItem>

/*
 * displays a screenshot in a background layer as well as the user's drawings in an overlying layer
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

    /*
     * MODIFIES:    this
     * EFFECTS:     sets the pen's colour to c
     */
    void setPenColour(QColor c);

public slots:
    /*
     * MODIFIES:    this
     * EFFECTS:     changes current mode to the given mode
     */
    void changeMode(Canvas::Mode mode);

    /*
     * MODIFIES:    this
     * EFFECTS:     if current mode is penMode, draws a line from previous point to given point with the pen
     *              if current mode is eraseMode, erases the top level item at the given point
     */
    void mouseDrag(QPoint point);

    /*
     * MODIFIES:    this
     * EFFECTS:     if current mode is penMode, draws a dot at the given point
     *              if current mode is eraseMode, erases the top level item at the given point
     */
    void mouseDown(QPoint point);

signals:

protected:
    /*
     * REQUIRES:    img is not null
     * MODIFIES:    this
     * EFFECTS:     sets background layer to img
     */
    void drawBackground(QPainter *painter, const QRectF &rect) override;


private:
    QPen pen;
    const QPixmap* img;
    qreal diameter;
    Mode currMode;
    QPoint lastPoint;

    /*
     * MODIFIES:    this
     * EFFECTS:     draws a line from previous point (lastPoint) to given point with the pen
     */
    void draw(QPoint point);

    /*
     * MODIFIES:    this
     * EFFECTS:     erases the items at the given point within a square that is twice as wide as the pen
     */
    void erase(QPoint point);
};

#endif // CANVAS_H
