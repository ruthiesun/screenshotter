#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsScene>

class Canvas : public QGraphicsScene
{
        Q_OBJECT
public:
    explicit Canvas(QObject *parent = nullptr);
    Canvas(QPixmap* img, QObject *parent = nullptr);

public slots:
    void AddDrawing(QPoint point);

signals:


protected:
    void drawBackground(QPainter *painter, const QRectF &rect) override;

private:
    const QPen pen;
    qreal diameter;
    bool mouseButtonDown;
    const QPixmap* img;

    void DrawDot(const QPointF point);

};

#endif // CANVAS_H
