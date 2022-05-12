#include "collectionscroller.h"
#include <QTreeView>
#include <QStandardItemModel>
#include <QIcon>
#include <QPixmap>
#include <QVariant>

CollectionScroller::CollectionScroller(QWidget* parent) : QScrollArea(parent) {
    Setup();
}

CollectionScroller::~CollectionScroller() {
    //!!!
}

void CollectionScroller::Add(const QPixmap* img, QStandardItem* parent) {
    model->Add(img, parent);
}



void CollectionScroller::Setup() {
    //delegate = new QAbstractItemDelegate(this);
    mainLayout = new QGridLayout(this);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    treeView = new QTreeView(this);
    treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //treeView->setUniformRowHeights(true);
treeView->setIconSize(QSize(300,100));
    //treeView->setItemDelegate(delegate);
    model = new CollectionModel(this);
    mainLayout->addWidget(treeView);

    treeView->setModel(model);
    treeView->expandAll();
}



