#ifndef SCREENSHOTEDITOR_H
#define SCREENSHOTEDITOR_H

#include <QGraphicsView>
#include <QStandardItem>
#include <QStandardItemModel>
#include "canvas.h"
#include "canvasviewer.h"
#include "collectionmodel.h"

/*
 * displays a single screenshot in a viewport and allows the user to manipulate it
 */
class ScreenshotEditor : public QWidget {
    Q_OBJECT
public:
    /*
     * EFFECTS:     constructor
     *              initializes the model to m
     */
    explicit ScreenshotEditor(CollectionModel* m, QWidget* parent = nullptr);

    /*
     * EFFECTS:     destructor
     */
    ~ScreenshotEditor();

    /*
     * EFFECTS:     returns model item of image that is currently displayed
     */
    QStandardItem* getCurrItem();

public slots:
    /*
     * MODIFIES:    this
     * EFFECTS:     switches display to the image at given index in the model
     *              if given index is invalid, displays a blank viewport
     *              if previous index is valid, updates the tree view icon of the previous image to display any modifications that the user has made
     */
    void changeView(const QModelIndex &current, const QModelIndex &previous);

    /*
     * MODIFIES:    this
     * EFFECTS:     removes references to item and deletes its associated canvas, if one exists
     */
    void itemWasDeleted(QStandardItem* item);

    /*
     * EFFECTS:     opens dialog that allows user to save image that is currently displayed
     */
    void save();

signals:
    void imgModified(QPixmap* img, QStandardItem* item);

protected:

private:
    /*
     * NOTE:        currImg is not deallocated with the ScreenshotEditor object
     */
    QStandardItem* currImg;
    /*
     * NOTE:        model is not deallocated with the ScreenshotEditor object
     */
    CollectionModel* model;

    Canvas* scene;
    CanvasViewer *viewer;
    QLayout* mainLayout;
    QHash<QStandardItem*, Canvas*> *itemToScene;

    /*
     * EFFECTS:     emits imgModified signal with image that is currently displayed, with its modifications
     */
    void signalImgModified(QStandardItem* item);

    /*
     * EFFECTS:     returns image that is currently displayed
     */
    QPixmap* getCurrScreenImg();
};

#endif // SCREENSHOTEDITOR_H
