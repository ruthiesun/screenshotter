#include "treeviewdelegate.h"
#include <iostream>
#include <QPainter>

TreeViewDelegate::TreeViewDelegate(QObject *parent) : QStyledItemDelegate{parent} {}


QSize TreeViewDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QSize size;
    if (index.data(Qt::DecorationRole).canConvert<QPixmap>()) {
        size = index.data(Qt::DecorationRole).value<QPixmap>().size();
    } else {
        std::cout << "ERROR: delegate failed to convert qvariant to qpixmap" << std::endl; //!!! replace with exception handling
    }

    return size.scaled(200,200,Qt::KeepAspectRatio);
}

void TreeViewDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QPixmap img;
    if (index.data(Qt::DecorationRole).canConvert<QPixmap>()) {
        img = index.data(Qt::DecorationRole).value<QPixmap>();
    } else {
        std::cout << "ERROR: delegate failed to convert qvariant to qpixmap" << std::endl; //!!! replace with exception handling
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
