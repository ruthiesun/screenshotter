#include "collectionviewer.h"
#include <QTreeView>
#include <QStandardItemModel>
#include <QIcon>
#include <QPixmap>
#include <QVariant>
#include <QHeaderView>
#include "treeviewdelegate.h"

CollectionViewer::CollectionViewer(CollectionModel* m, QWidget* parent) : QTreeView(parent) {
    model = m;
    setup();
}

void CollectionViewer::setup() {
    this->setHeaderHidden(true);
    this->header()->resizeSections(QHeaderView::ResizeToContents);
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    delete(this->itemDelegate());
    this->setItemDelegate(new TreeViewDelegate(this->width()));
    this->setModel(model);
    this->expandAll();
    this->setAnimated(true);
}



