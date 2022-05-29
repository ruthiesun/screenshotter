#ifndef COLLECTIONMODEL_H
#define COLLECTIONMODEL_H

#include <QStandardItemModel>

/*
 * model for the user's collection of screenshots for the current session
 */
class CollectionModel : public QStandardItemModel {
    Q_OBJECT
public:
    explicit CollectionModel(QObject *parent = nullptr);

    /*
     * MODIFIES: this
     * EFFECTS: adds img to the model under the given parent
     *          img is added to a new row if parent == nullptr
     */
    void Add(const QPixmap* img, QStandardItem* parent = nullptr);

    /*
     * !!!
     */
    void Delete(QStandardItem* parent = nullptr);

    /*
     * REQUIRES: item is in the model
     * EFFECTS: returns pointer to lowest level QStandardItem that is a parent of item
     */
    QStandardItem* FindParent(QStandardItem* item);

public slots:
    /*
     * MODIFIES: this
     * EFFECTS: changes item's DecorationRole image to img
     */
    void ChangeDecoration(const QPixmap* img, QStandardItem* item);

signals:
    void Cleared(QStandardItem* item);

private:
    void emitCleared(QStandardItem* item);
};

#endif // COLLECTIONMODEL_H
