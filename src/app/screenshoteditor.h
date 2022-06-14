#ifndef SCREENSHOTEDITOR_H
#define SCREENSHOTEDITOR_H

#include <QGraphicsView>
#include <QStandardItem>
#include <QStandardItemModel>
#include "canvas.h"
#include "canvasviewer.h"
#include "collectionmodel.h"
#include "saver.h"

/*
 * displays a single screenshot in a viewport and allows the user to add drawings to it
 */
class ScreenshotEditor : public QWidget {
    Q_OBJECT
public:
    /*
     * REQUIRES:    m is not null
     * EFFECTS:     constructor
     *              initializes the model to m
     */
    explicit ScreenshotEditor(CollectionModel* m, QWidget* parent = nullptr);

    /*
     * EFFECTS:     destructor
     */
    ~ScreenshotEditor();

    /*
     * EFFECTS:     returns model item of image that is currently displayed (currImgItem)
     */
    QStandardItem* getCurrItem();

    /*
     * EFFECTS:     copies currently-displayed image to clipboard
     *              if no image is displayed, does nothing
     */
    void toClipboard();

public slots:
    /*
     * MODIFIES:    this
     * EFFECTS:     switches display to the image at given index in the model
     *              if given index is invalid, displays a blank viewport
     */
    void changeView(const QModelIndex &current, const QModelIndex &previous);

    /*
     * MODIFIES:    this
     * EFFECTS:     if item is in the itemToScene hashmap, removes that entry
     */
    void itemWasDeleted(QStandardItem* item);

    /*
     * EFFECTS:     opens dialog that allows user to save image that is currently displayed
     *              default file type is .png
     */
    void save();

    /*
     * EFFECTS:     repaints the areas of the current image listed in the given list of regions
     *              emits an imgModified signal with the current model item and an image containing the current image with its drawings
     */
    void imgRegionsChanged(const QList<QRectF> &region);

    /*
     * EFFECTS:     if there is an image in the viewport, change the pen colour to c
     *              else, does nothing
     */
    void changePenColour(QColor c);

signals:
    void imgModified(QPixmap* img, QStandardItem* item);
    void changingToParentItem(QStandardItem* item, QStandardItem* itemParent); //!!! change name once colourselector is refactored to use a disjoint set

private:
    /*
     * NOTE:        currImgItem is not deallocated with the ScreenshotEditor object
     */
    QStandardItem* currImgItem;

    /*
     * NOTE:        model is not deallocated with the ScreenshotEditor object
     */
    CollectionModel* model;

    Canvas* scene;
    CanvasViewer *viewer;
    QLayout* mainLayout;
    QHash<QStandardItem*, Canvas*> *itemToScene;
    QPixmap currImg;
    Saver saver;

    /*
     * EFFECTS:     emits imgModified signal with img and the current QStandardItem being displayed
     */
    void signalImgModified(QPixmap* img);

    /*
     * EFFECTS:     returns image that is currently displayed, bounded by either the original image or the user's drawings
     */
    QPixmap* getCurrScreenImg();
};

#endif // SCREENSHOTEDITOR_H
