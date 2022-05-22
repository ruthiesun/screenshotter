#include "treeviewdelegate.h"
#include <iostream>
#include <QPainter>

TreeViewDelegate::TreeViewDelegate(QObject *parent) : QStyledItemDelegate{parent} {}

QSize TreeViewDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    try {
        QSize size = index.data(Qt::DecorationRole).value<QPixmap>().size();
        return size.scaled(200,200,Qt::KeepAspectRatio);
    } catch (_exception& e) {
        throw std::domain_error("TreeViewDelegate::sizeHint - QVariant conversion failure");
    }
}

void TreeViewDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QPixmap img;
    try {
        img = index.data(Qt::DecorationRole).value<QPixmap>();
    } catch (_exception& e) {
        throw std::domain_error("TreeViewDelegate::paint - QVariant conversion failure");
    }

    QStyleOptionViewItem styleOption = QStyleOptionViewItem(option);
    initStyleOption(&styleOption, index);
    styleOption.decorationSize = sizeHint(option, index);
    QRect rect = styleOption.rect;
    QPoint topLeft = rect.topLeft();
    QRect newRect = QRect(topLeft.x(), topLeft.y(), styleOption.decorationSize.width(), styleOption.decorationSize.height());

    painter->save();
    painter->drawPixmap(newRect, img);
    painter->restore();
}
