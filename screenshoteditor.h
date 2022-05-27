#ifndef SCREENSHOTEDITOR_H
#define SCREENSHOTEDITOR_H

#include <QGraphicsView>
#include <QHBoxLayout>
#include <QStandardItem>
#include <QStandardItemModel>
#include "canvas.h"
#include "canvasviewer.h"
#include "collectionmodel.h"

/*
 * displays a single screenshot and allows the user to manipulate it
 */
class ScreenshotEditor : public QWidget {
    Q_OBJECT
public:
    /*
     * EFFECTS: initializes the model to m
     */
    explicit ScreenshotEditor(CollectionModel* m, QWidget* parent = nullptr);
    ~ScreenshotEditor();

    QStandardItem* GetCurrImg();


public slots:
    /*
     * EFFECTS: switches display to the image at given index in the model (current)
     *          scenes are preserved between switches
     */
    void ChangeView(const QModelIndex &current, const QModelIndex &previous);
    void Save();

signals:
    //!!!
    void ImgChanged(QPixmap* img, QStandardItem* item);

protected:

private:
    QStandardItem* currImg;
    CollectionModel* model;
    Canvas* scene;
    CanvasViewer* viewer;
    QLayout* mainLayout;
    QHash<QStandardItem*, Canvas*> *itemToScene;

    void UpdateView(QStandardItem* item);
    QPixmap* GetCurrScreenImg();

};

#endif // SCREENSHOTEDITOR_H
