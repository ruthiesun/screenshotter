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
     * EFFECTS:     deletes item from the model and all its children
     *              emits a Cleared signal for each deleted item/child
     */
    void deleteImg(QStandardItem* item);

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
    /*
     * REQUIRES:    item is in the model
     *              item is not null
     * EFFECTS:     emits a deleted signal for item and all its children
     */
    void signalDeleted(QStandardItem* item);
};

#endif // COLLECTIONMODEL_H
