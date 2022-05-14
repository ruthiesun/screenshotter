#include "collectionviewer.h"
#include <QTreeView>
#include <QStandardItemModel>
#include <QIcon>
#include <QPixmap>
#include <QVariant>
#include <QHeaderView>

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

void CollectionViewer::Add(const QPixmap* img, QStandardItem* parent) {
    model->Add(img, parent);
}

void CollectionViewer::Setup() {

    this->setHeaderHidden(true);
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QHeaderView *verticalHeader = this->header();

    verticalHeader->setSectionResizeMode(QHeaderView::Fixed);
    verticalHeader->setMaximumSectionSize(1);

    this->setModel(model);
    this->expandAll();
}



