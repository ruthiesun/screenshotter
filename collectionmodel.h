#ifndef COLLECTIONMODEL_H
#define COLLECTIONMODEL_H

#include <QStandardItemModel>

/*
 * model for the user's collection of screenshots for the current session
 */
class CollectionModel : public QStandardItemModel {
    Q_OBJECT
public:
    using QStandardItemModel::QStandardItemModel;

    /*
     * MODIFIES:    this, parent
     * EFFECTS:     adds img to the model under the given parent
     *              img is added to a new row if parent == nullptr
     *              returns a pointer to the new item
     */
    QStandardItem* addImg(const QPixmap *img, QStandardItem* parent = nullptr);

    /*
     * REQUIRES:    item is in the model
     *              item is not null
     * MODIFIES:    this, item
     * EFFECTS:     deletes item from the model and emits a deleted signal for it
     *              if item was a root with children, makes first child adopt all the other children, sets that child as the new root, and return a pointer to it
     *              if item was a root without children, returns nullptr
     *              if item was a child, deletes the child and returns a pointer to its root
     */
    QStandardItem* deleteImg(QStandardItem* item);

    /*
     * REQUIRES:    item is in the model
     *              item is not null
     * EFFECTS:     returns pointer to lowest level QStandardItem that is a parent of item
     */
    QStandardItem* findParent(QStandardItem* item);

public slots:
    /*
     * MODIFIES:    this, item
     * EFFECTS:     changes item's DecorationRole image to img
     */
    void changeDecoration(const QPixmap* img, QStandardItem* item);

signals:
    void deleted(QStandardItem* item);

private:

};

#endif // COLLECTIONMODEL_H
