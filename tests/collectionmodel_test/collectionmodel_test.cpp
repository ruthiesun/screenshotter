#include <QtTest>
#include <QCoreApplication>
#include "collectionmodel.h"

// add necessary includes here

class CollectionModel_Test : public QObject
{
    Q_OBJECT

public:
    CollectionModel_Test();
    ~CollectionModel_Test();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    void addImgToInvisibleRootItem();
    void addImgToExistingItem();
    void deleteImg();
    void findParent();
    void changeDecoration();

private:
    //CollectionModel model;
    //const QPixmap* img;
};

CollectionModel_Test::CollectionModel_Test() {
    //img = new QPixmap(10,10);
}

CollectionModel_Test::~CollectionModel_Test() {
    //delete img;
}

void CollectionModel_Test::initTestCase() {

}

void CollectionModel_Test::cleanupTestCase() {

}

void CollectionModel_Test::init() {

}

void CollectionModel_Test::cleanup() {
    //delete model;
}

void CollectionModel_Test::addImgToInvisibleRootItem() {
    QVERIFY(1 != 2);
    QVERIFY(2 != 2);

    CollectionModel m;
    /*
    QVERIFY(model->hasChildren(model->invisibleRootItem()->index()) == false);

    QStandardItem* item = model->CollectionModel::addImg(img);

    QVERIFY(model->hasChildren(model->invisibleRootItem()->index()) == true);
    QVERIFY(item != nullptr);
    */

}

void CollectionModel_Test::addImgToExistingItem() {

}

void CollectionModel_Test::deleteImg() {

}

void CollectionModel_Test::findParent() {

}

void CollectionModel_Test::changeDecoration() {

}

QTEST_MAIN(CollectionModel_Test)

#include "collectionmodel_test.moc"
