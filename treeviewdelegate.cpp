#include "treeviewdelegate.h"
#include <QPainter>

TreeViewDelegate::TreeViewDelegate(int viewWidth, QObject * parent) : QStyledItemDelegate(parent) {
    this->viewWidth = viewWidth;
}


QSize TreeViewDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    try {
        QSize size = index.data(Qt::DecorationRole).value<QPixmap>().size();
        return size.scaled(viewWidth, viewWidth ,Qt::KeepAspectRatio);
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
    QSize totalSize = sizeHint(option, index);
    styleOption.decorationSize = QSize(totalSize.width()-1, totalSize.height()-1);
    QRect rect = styleOption.rect;
    QPoint topLeft = rect.topLeft();
    QRect newRect = QRect(topLeft.x(), topLeft.y(), styleOption.decorationSize.width(), styleOption.decorationSize.height());

    painter->save();
    painter->drawPixmap(newRect, img);
    painter->restore();
}
