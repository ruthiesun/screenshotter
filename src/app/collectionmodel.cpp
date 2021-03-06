#include "collectionmodel.h"
#include <exception>
#include <iostream>

QStandardItem* CollectionModel::addImg(const QPixmap* img, QStandardItem* parent) {
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

    return newImg;
}

QStandardItem* CollectionModel::deleteImg(QStandardItem *item) {
    emit deleted(item);
    int itemRow = item->row();

    if (item->hasChildren()) {
        QStandardItem* oldParentItem = invisibleRootItem()->takeRow(item->row()).at(0);
        QStandardItem* newParentItem = oldParentItem->takeRow(0).at(0);
        while (oldParentItem->rowCount() > 0) {
            QList<QStandardItem*> childRow = oldParentItem->takeRow(0);
            newParentItem->appendRow(childRow.at(0));
        }
        invisibleRootItem()->insertRow(itemRow, newParentItem);
        delete item;
        return newParentItem;

    } else {
        QStandardItem* parent = findParent(item);
        delete item;
        if (item != parent) {
            removeRow(itemRow, parent->index());
            return parent;
        } else {
            removeRow(itemRow, invisibleRootItem()->index());
            return nullptr;
        }
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
