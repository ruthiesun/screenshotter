#include <QtTest>
#include <QCoreApplication>

// add necessary includes here

class MainWindowTest : public QObject {
    Q_OBJECT

public:
    MainWindowTest();
    ~MainWindowTest();

private slots:
    void initTestCase();
    void cleanupTestCase();

    void MainWindow(QWidget *parent);
    void sizeHint();
    void parseToolbarSignal(QAction* action);
    void addScreenshot(QPixmap* img);

    void setupToolbar();
    void setup();
    void makeNewCanvas();
    void deleteCanvas();
    void openCamera();

    //destructor
    //void canvasModeChanged(Canvas::Mode mode); //a signal
};

MainWindowTest::MainWindowTest() {

}

MainWindowTest::~MainWindowTest() {

}

void MainWindowTest::initTestCase() {
    qDebug("i am wokring");
}

void MainWindowTest::cleanupTestCase() {

}

void MainWindowTest::MainWindow(QWidget *parent) {

}

void MainWindowTest::sizeHint() {

}

void MainWindowTest::parseToolbarSignal(QAction* action) {

}

void MainWindowTest::addScreenshot(QPixmap* img) {

}

void MainWindowTest::setupToolbar() {

}

void MainWindowTest::setup() {

}
void MainWindowTest::makeNewCanvas() {

}

void MainWindowTest::deleteCanvas() {

}

void MainWindowTest::openCamera() {

}


QTEST_MAIN(MainWindowTest)

#include "mainwindowtest.moc"
