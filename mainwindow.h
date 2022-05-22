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
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /*
     * EFFECTS: takes a screenshot and adds it to the user's collection
     */
    void AddScreenshot();

public slots:
    /*
     * REQUIRES: action was signalled from the toolbar
     * EFFECTS: responds to the button pressed on the toolbar
     */
    void ParseToolbarSignal(QAction* action);

signals:

private:
    const QString DRAW = "Draw";
    const QString ERASE = "Erase";
    const QString CROP = "Crop";
    const QString SAVE_CHANGES = "Save changes";
    const QString SAVE_TO_FILE = "Save to file";
    const QString NEW_COPY = "New copy";
    const QString DELETE = "Delete";
    const QString NEW_SCREENSHOT = "Take new screenshot";

    QWidget* centralWidget;
    CollectionViewer* scroller;
    QToolBar* toolbar;
    ScreenshotEditor* editor;
    QHBoxLayout* mainLayout;
    QGridLayout* editAreaLayout;
    CollectionModel* model;


    /*
     * EFFECTS: sets up toolbar; called by constructor
     */
    void SetupToolbar();
};
#endif // MAINWINDOW_H
