#include "treeviewdelegate.h"
#include <iostream>

TreeViewDelegate::TreeViewDelegate(QObject *parent) : QStyledItemDelegate{parent} {}


QSize TreeViewDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QPixmap img = qvariant_cast<QPixmap>(index.data());
    QSize size = img.size();
    return size.scaled(50,50,Qt::KeepAspectRatio);
    std::cout << "asking delegating for size" << std::endl;

}
