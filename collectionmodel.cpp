#include "collectionmodel.h"
#include <exception>
#include <iostream>

void CollectionModel::Add(const QPixmap* img, QStandardItem* parent) {
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

void CollectionModel::Delete(QStandardItem *item) {
    emitCleared(item);

    QStandardItem* parent = this->FindParent(item);

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
        delete(item);
        removeRow(row, parent->index());
    }

}

void CollectionModel::emitCleared(QStandardItem* item) {
    emit Cleared(item);
    for (int i=0; i<item->rowCount(); i++) {
        emitCleared(item->child(i));
    }
}

QStandardItem* CollectionModel::FindParent(QStandardItem* item) {
    try {
        if (item->parent() == nullptr) {
            return item;
        }
    } catch (_exception& e) {
        throw std::invalid_argument("CollectionModel::FindParent - nullptr arg");
    }
    return FindParent(item->parent());
}

void CollectionModel::ChangeDecoration(const QPixmap* img, QStandardItem* item) {
    item->setData(*img, Qt::DecorationRole);
}
