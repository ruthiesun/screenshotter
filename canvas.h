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
    void ParseMouse(QPoint point);
    void MouseRelease();

signals:


protected:
    void drawBackground(QPainter *painter, const QRectF &rect) override;

private:
    const QPen pen;
    qreal diameter;
    const QPixmap* img;
    enum Mode { penMode, eraseMode };
    Mode currMode;

    void Draw(QPoint point);
    void Erase(QPoint point);
    void Setup();
};

#endif // CANVAS_H
