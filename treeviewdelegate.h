#ifndef TREEVIEWDELEGATE_H
#define TREEVIEWDELEGATE_H

#include <QStyledItemDelegate>

/*
 * delegate for the tree view of the screenshot collection
 */
class TreeViewDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit TreeViewDelegate(QObject *parent = nullptr);
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    /*
     * EFFECTS: displays each tree node as the image that it represents, with a size dictated by sizeHint
     */
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // TREEVIEWDELEGATE_H
