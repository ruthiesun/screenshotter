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
    Setup();
}

CollectionViewer::~CollectionViewer() {
    //!!!
}

QTreeView* CollectionViewer::GetView() {
    return this;
}

void CollectionViewer::Setup() {
    this->setHeaderHidden(true);
    this->header()->resizeSections(QHeaderView::ResizeToContents);
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    //this->setUniformRowHeights(true);
    delete(this->itemDelegate());
    this->setItemDelegate(new TreeViewDelegate());

    this->setModel(model);
    this->expandAll();
}



