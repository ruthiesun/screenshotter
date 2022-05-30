#include "collectionmodel.h"
#include <exception>
#include <iostream>

void CollectionModel::addImg(const QPixmap* img, QStandardItem* parent) {
    QStandardItem *rootNode;
    if (parent == nullptr) {
        rootNode = invisibleRootItem();
    } else {
        rootNode = parent;
    }

    QStandardItem *newImg = new QStandardItem();
    newImg->setData(*img, Qt::DecorationRole);
    newImg->setData(*img, Qt::UserRole);
    rootNode->appendRow(newImg);
}

void CollectionModel::deleteImg(QStandardItem *item) {
    signalDeleted(item);

    QStandardItem* parent = this->findParent(item);

    if (item == parent) {
        for (int i=0; i<item->rowCount(); i++) {
            delete item->child(i);
            item->removeRow(i);
        }
        int row = item->row();
        delete item;
        invisibleRootItem()->removeRow(row);

    } else {
        int row = item->row();
        delete item;
        removeRow(row, parent->index());
    }

}

void CollectionModel::signalDeleted(QStandardItem* item) {
    emit deleted(item);
    for (int i=0; i<item->rowCount(); i++) {
        signalDeleted(item->child(i));
    }
}

QStandardItem* CollectionModel::findParent(QStandardItem* item) {
    try {
        if (item->parent() == nullptr) {
            return item;
        }
    } catch (_exception& e) {
        throw std::invalid_argument("CollectionModel::FindParent - nullptr arg");
    }
    return findParent(item->parent());
}

void CollectionModel::changeDecoration(const QPixmap* img, QStandardItem* item) {
    item->setData(*img, Qt::DecorationRole);
}
