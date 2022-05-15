#include "collectionmodel.h"
#include <iostream>

CollectionModel::CollectionModel(QObject *parent) : QStandardItemModel{parent} {
}

void CollectionModel::Add(const QPixmap* img, QStandardItem* parent) {
    QStandardItem *rootNode;
    if (parent == nullptr) {
        std::cout << "nulptr" << std::endl;
        rootNode = invisibleRootItem();
    } else {
        rootNode = parent;
    }
    //!!! figure out how to store full image data in QStandardItem
    QStandardItem *newImg = new QStandardItem();
   // QVariant* var = new QVariant(img);
    newImg->setData(*img, Qt::DecorationRole);

    rootNode->appendRow(newImg);
}

QStandardItem* CollectionModel::FindParent(QStandardItem* item) {
    if (item == nullptr) {
        std::cout << "invalid input for CollectionModel::FindParent (nullptr)" << std::endl; //!! replace with exception
    }
    if (item->parent() == nullptr) {
        return item;
    }
    return FindParent(item->parent());
}
