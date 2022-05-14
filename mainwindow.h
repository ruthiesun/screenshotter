#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QToolButton>
#include "collectionviewer.h"
#include "screenshoteditor.h"
#include <QStandardItem>
#include "collectionmodel.h"

/*
 * class representing the application's window
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    const QString DRAW = "Draw";
    const QString ERASE = "Erase";
    const QString CROP = "Crop";
    const QString SAVE_CHANGES = "Save changes";
    const QString SAVE_TO_FILE = "Save to file";
    const QString NEW_COPY = "New copy";
    const QString DELETE = "Delete";

    /*
     * EFFECTS: constructor
     */
    MainWindow(QWidget *parent = nullptr);

    /*
     * EFFECTS: destructor
     */
    ~MainWindow();

    /*
     * EFFECTS: takes a screenshot and adds it to the user's collection
     */
    void AddScreenshot();

public slots:

    /*
     * REQUIRES: action was signalled from the toolbar
     * EFFECTS: determines the source of the signal begins an appropriate response
     */
    void ParseToolbarSignal(QAction* action);

signals:

private:
    QWidget* centralWidget;
    CollectionViewer* scroller;
    QToolBar* toolbar;
    ScreenshotEditor* editor;
    QHBoxLayout* mainLayout;
    QGridLayout* editAreaLayout;
    CollectionModel* model;


    /*
     * EFFECTS: sets up toolbar that allows user to modify a screenshot
     *          called by constructor
     */
    void SetupToolbar();
};
#endif // MAINWINDOW_H
