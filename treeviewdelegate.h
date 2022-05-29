#ifndef TREEVIEWDELEGATE_H
#define TREEVIEWDELEGATE_H

#include <QStyledItemDelegate>

/*
 * delegate for the tree view of the screenshot collection
 */
class TreeViewDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    using QStyledItemDelegate::QStyledItemDelegate;

    /*
     * EFFECTS:     scales the size of the image at the given index such that any dimension is at most 200 pixels and returns this size
     */
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    /*
     * EFFECTS:     displays each tree node as its DecorationRole image, with a size dictated by sizeHint
     */
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // TREEVIEWDELEGATE_H
