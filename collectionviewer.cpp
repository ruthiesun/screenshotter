#include "collectionviewer.h"
#include <QTreeView>
#include <QStandardItemModel>
#include <QIcon>
#include <QPixmap>
#include <QVariant>
#include <QHeaderView>
#include "treeviewdelegate.h"
#include <QGuiApplication>
#include <QScreen>
#include "mainwindow.h"

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
    this->setModel(model);
    this->expandAll();
    this->setAnimated(true);
}

void CollectionViewer::initDelegate() {
    QSize fullSize = QGuiApplication::primaryScreen()->size();
    this->setItemDelegate(new TreeViewDelegate(fullSize.width()*((double)MainWindow::scrollerRatioValue/(double)MainWindow::editorRatioValue)*0.6));
}





