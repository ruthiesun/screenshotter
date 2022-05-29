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
     * MODIFIES:    this
     * EFFECTS:     adds img to the model under the given parent
     *              img is added to a new row if parent == nullptr
     */
    void Add(const QPixmap* img, QStandardItem* parent = nullptr);

    /*
     * REQUIRES:    item is in the model
     *              item is not null
     * MODIFIES:    this
     * EFFECTS:     deletes item from the model and all its children
     *              emits a Cleared signal for each deleted item/child
     */
    void Delete(QStandardItem* item);

    /*
     * REQUIRES:    item is in the model
     *              item is not null
     * EFFECTS:     returns pointer to lowest level QStandardItem that is a parent of item
     */
    QStandardItem* FindParent(QStandardItem* item);

public slots:
    /*
     * MODIFIES:    this
     * EFFECTS:     changes item's DecorationRole image to img
     */
    void ChangeDecoration(const QPixmap* img, QStandardItem* item);

signals:
    void Cleared(QStandardItem* item);

private:
    /*
     * REQUIRES:    item is in the model
     *              item is not null
     * EFFECTS:     emits a Cleared signal for item and all its children
     */
    void emitCleared(QStandardItem* item);
};

#endif // COLLECTIONMODEL_H
