#ifndef SCREENSHOTEDITOR_H
#define SCREENSHOTEDITOR_H

#include <QGraphicsView>
#include <QHBoxLayout>

/*
 * a widget that displays a single screenshot and allows the user to manipulate it
 */
class ScreenshotEditor : public QWidget {
    Q_OBJECT
public:
    /*
     * EFFECTS: constructor (does not display an image)
     */
    explicit ScreenshotEditor(QWidget* parent = nullptr);

    /*
     * EFFECTS: constructor
     */
    ScreenshotEditor(QPixmap* img, QWidget* parent = nullptr);

public slots:

signals:

private:
    QPixmap* currImg;
    QGraphicsPixmapItem* item;
    QGraphicsScene* scene;
    QGraphicsView* viewer;
    QLayout* mainLayout;

    /*
     * EFFECTS: sets up graphics viewing fields; called by cosntructor
     */
    void Setup();
};

#endif // SCREENSHOTEDITOR_H
