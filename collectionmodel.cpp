#include "collectionmodel.h"
#include <iostream>
#include <exception>

CollectionModel::CollectionModel(QObject *parent) : QStandardItemModel{parent} {}

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
        clearItemData(item->index());
        if (invisibleRootItem()->rowCount() == 1) {
            clear();
        } else {
            invisibleRootItem()->removeRow(item->row());
        }
    } else {
        removeRow(item->row(), parent->index());
    }
}

void CollectionModel::emitCleared(QStandardItem* item) {
    emit Cleared(item);
    for (int i=0; i<item->rowCount(); i++) {
        std::cout << i << std::endl;
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
