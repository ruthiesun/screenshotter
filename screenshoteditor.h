#ifndef SCREENSHOTEDITOR_H
#define SCREENSHOTEDITOR_H

#include <QGraphicsView>
#include <QHBoxLayout>
#include <QStandardItem>
#include <QStandardItemModel>
#include "canvas.h"
#include "canvasviewer.h"

/*
 * displays a single screenshot and allows the user to manipulate it
 */
class ScreenshotEditor : public QWidget {
    Q_OBJECT
public:
    /*
     * EFFECTS: initializes the model to m
     */
    explicit ScreenshotEditor(QStandardItemModel* m, QWidget* parent = nullptr);
    ~ScreenshotEditor();

    QStandardItem* GetCurrImg();

public slots:
    /*
     * EFFECTS: switches display to the image at given index in the model (current)
     *          scenes are preserved between switches
     */
    void ChangeView(const QModelIndex &current, const QModelIndex &previous);

signals:

protected:

private:
    QStandardItem* currImg;
    QStandardItemModel* model;
    Canvas* scene;
    CanvasViewer* viewer;
    QLayout* mainLayout;
    QHash<QStandardItem*, Canvas*> *itemToScene;

};

#endif // SCREENSHOTEDITOR_H
