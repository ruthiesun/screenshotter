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
    QStandardItem *newImg = new QStandardItem();
    QVariant* var = new QVariant(img);
    newImg->setData(*var);
    newImg->setData(*img, Qt::DecorationRole);

    rootNode->appendRow(newImg);
}
