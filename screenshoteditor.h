#ifndef SCREENSHOTEDITOR_H
#define SCREENSHOTEDITOR_H

#include <QGraphicsView>
#include <QHBoxLayout>
#include <QStandardItem>
#include <QStandardItemModel>
#include "canvas.h"
#include "canvasviewer.h"

/*
 * a widget that displays a single screenshot and allows the user to manipulate it
 */
class ScreenshotEditor : public QWidget {
    Q_OBJECT
public:
    /*
     * EFFECTS: constructor (does not display an image)
     */
    explicit ScreenshotEditor(QStandardItemModel* m, QWidget* parent = nullptr);


    QStandardItem* GetCurrImg();

public slots:
    void ChangeView(const QModelIndex &current, const QModelIndex &previous);

signals:

protected:

private:
    QStandardItem* currImg;
    QStandardItemModel* model;
    //QGraphicsPixmapItem* item;
    Canvas* scene;
    CanvasViewer* viewer;
    //QGraphicsView* viewer;
    QLayout* mainLayout;


    /*
     * EFFECTS: sets up connections
     */
    void Setup();
};

#endif // SCREENSHOTEDITOR_H
