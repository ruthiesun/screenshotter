#ifndef COLLECTIONVIEWER_H
#define COLLECTIONVIEWER_H

#include <QScrollArea>
#include <QTreeView>
#include <QStandardItemModel>
#include <QGridLayout>
#include "collectionmodel.h"

/*
 * widget for displaying a view of the user's collection of screenshots for the current session
 */
class CollectionViewer : public QTreeView {
    Q_OBJECT
public:
    /*
     * REQUIRES:    m is not null
     * EFFECTS:     constructor
     *              initializes model to m
     */
    explicit CollectionViewer(CollectionModel* m, QWidget* parent = nullptr);

    /*
     * EFFECTS:     sets up delegate for this
     */
    void initDelegate();

private:
    /*
     * NOTE:        model is not deallocated with the CollectionViewer object
     */
    CollectionModel* model;

    /*
     * MODIFIES:    this
     * EFFECTS:     sets up the ui
     *              called by the constructor
     */
    void setup();

};

#endif // COLLECTIONVIEWER_H
