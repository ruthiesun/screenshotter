#ifndef COLLECTIONMODEL_H
#define COLLECTIONMODEL_H

#include <QStandardItemModel>

/*
 * model for the user's collection of screenshots for the current session
 */
class CollectionModel : public QStandardItemModel
{
    Q_OBJECT
public:
    /*
     * EFFECTS: default QStandardItemModel constructor
     */
    explicit CollectionModel(QObject *parent = nullptr);

    /*
     * MODIFIES: this
     * EFFECTS: adds img to the model under the given parent
     *          img is added to a new row if parent == nullptr
     */
    void Add(const QPixmap* img, QStandardItem* parent = nullptr);

    /*
     * REQURIES: item is in this model
     * EFFECTS: returns pointer to lowest level QStandardItem in the tree that contains item
     */
    QStandardItem* FindParent(QStandardItem* item);

public slots:

signals:

private:

};

#endif // COLLECTIONMODEL_H
