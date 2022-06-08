#ifndef SCREENSHOTEDITOR_H
#define SCREENSHOTEDITOR_H

#include <QGraphicsView>
#include <QStandardItem>
#include <QStandardItemModel>
#include "canvas.h"
#include "canvasviewer.h"
#include "collectionmodel.h"
#include <QClipboard>

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

    /*
     * EFFECTS:     copies currently-displayed image to clipboard
     */
    void toClipboard();

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

    /*
     * EFFECTS:     emits an imgModified signal for the current image and copies the image to clipboard
     */
    void imgRegionsChanged(const QList<QRectF> &region);

    /*
     * EFFECTS:     if there is an image in the viewport, change the pen colour to c
     *              else, does nothing
     */
    void changePenColour(QColor c);

signals:
    void imgModified(QPixmap* img, QStandardItem* item);
    void changingToParentItem(QStandardItem* item);

private:
    /*
     * NOTE:        currImgImg is not deallocated with the ScreenshotEditor object
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
    QClipboard* clipboard;
    QPixmap currImg;

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
