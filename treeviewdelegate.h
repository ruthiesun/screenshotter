#ifndef TREEVIEWDELEGATE_H
#define TREEVIEWDELEGATE_H

#include <QStyledItemDelegate>

/*
 * delegate for the tree view of the screenshot collection (SelectionViewer class)
 */
class TreeViewDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    /*
     * EFFECTS:     constructor
     *              sets this->viewWidth to viewWidth
     */
    explicit TreeViewDelegate(int viewWidth, QObject * parent = nullptr);

    /*
     * EFFECTS:     scales the size of the image at the given index such that it fits into viewWidth and returns this size
     */
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    /*
     * EFFECTS:     displays each tree node as its DecorationRole image, with a size dictated by sizeHint
     */
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    int viewWidth;
};

#endif // TREEVIEWDELEGATE_H
