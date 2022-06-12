#include <QtTest>
#include <QCoreApplication>
#include "collectionmodel.h"


class CollectionModelTest : public QObject {
    Q_OBJECT

public:
    CollectionModelTest();
    ~CollectionModelTest();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    void addImgTest();
    void deleteImgTest();
    void findParentTest();
    void changeDecorationTest();

private:
    //CollectionModel model;
};

CollectionModelTest::CollectionModelTest() {

}

CollectionModelTest::~CollectionModelTest() {

}

void CollectionModelTest::initTestCase() {

}

void CollectionModelTest::cleanupTestCase() {

}

void CollectionModelTest::addImgTest() {

}

void CollectionModelTest::deleteImgTest() {

}

void CollectionModelTest::findParentTest() {

}

void CollectionModelTest::changeDecorationTest() {

}


QTEST_MAIN(CollectionModelTest)

#include "collectionmodeltest.moc"
