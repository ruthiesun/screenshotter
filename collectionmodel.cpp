#include "collectionmodel.h"

CollectionModel::CollectionModel(QObject *parent) : QStandardItemModel{parent} {
}

void CollectionModel::Add(const QPixmap* img, QStandardItem* parent) {
    QStandardItem *rootNode;
    if (parent == nullptr) {
        rootNode = invisibleRootItem();
    } else {
        rootNode = parent;
    }
    //!!! figure out how to store full image data in QStandardItem
    QStandardItem *newImg = new QStandardItem();
    QVariant* var = new QVariant(img);
    newImg->setData(*img, Qt::UserRole);
    newImg->setData(*img, Qt::DecorationRole);

    rootNode->appendRow(newImg);
}
