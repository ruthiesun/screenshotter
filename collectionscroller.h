#ifndef COLLECTIONSCROLLER_H
#define COLLECTIONSCROLLER_H

#include <QScrollArea>
#include <QTreeView>
#include <QStandardItemModel>
#include <QGridLayout>
#include "collectionmodel.h"

/*
 * widget for displaying a view of the user's collection of screenshots for the current session
 */
class CollectionScroller : public QScrollArea {
    Q_OBJECT
public:
    /*
     * EFFECTS: constructor; sets up display
     */
    explicit CollectionScroller(CollectionModel* m, QWidget* parent = nullptr);

    /*
     * EFFECTS: destructor
     */
    ~CollectionScroller();

    QTreeView* GetView();

public slots:
    /*
     * MODIFIES: this
     * EFFECTS: adds img to the scroller's model under the given parent
     *          img is added to a new row if parent == nullptr
     */
    void Add(const QPixmap* img, QStandardItem* parent = nullptr);

signals:
    /*
     * EFFECTS: sends a signal with an image from the collection
     */
    void SelectedForView(QPixmap* img);

private:
    QTreeView* treeView;
    CollectionModel* model;
    QAbstractItemDelegate* delegate;
    QGridLayout* mainLayout;

    /*
     * EFFECTS: sets up the display; called by constructor
     */
    void Setup();

};

#endif // COLLECTIONSCROLLER_H
