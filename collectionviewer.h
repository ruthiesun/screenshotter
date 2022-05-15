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
     * EFFECTS: constructor; sets up display
     */
    explicit CollectionViewer(CollectionModel* m, QWidget* parent = nullptr);

    /*
     * EFFECTS: destructor
     */
    ~CollectionViewer();

    QTreeView* GetView();

public slots:
    /*
     * MODIFIES: this
     * EFFECTS: adds img to the scroller's model under the given parent
     *          img is added to a new row if parent == nullptr
     */
    //void Add(const QPixmap* img, QStandardItem* parent = nullptr);

signals:
    /*
     * EFFECTS: sends a signal with an image from the collection
     */
    void SelectedForView(QPixmap* img);

private:
    CollectionModel* model;

    /*
     * EFFECTS: sets up the display; called by constructor
     */
    void Setup();

};

#endif // COLLECTIONVIEWER_H
