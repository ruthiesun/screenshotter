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
#include "camera.h"
#include "collectionmodel.h"
#include "canvas.h"

/*
 * class representing the application's window
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    /*
     * REQUIRES: action was signalled from the toolbar
     * EFFECTS: responds to the button pressed on the toolbar
     */
    void ParseToolbarSignal(QAction* action);

    /*
     * REQUIRES: img non-null
     * EFFECTS: takes a screenshot and adds it to the user's collection
     */
    void AddScreenshot(QPixmap* img);

signals:
    void CanvasModeChanged(Canvas::Mode mode);

private:
    const QString DRAW = "Draw";
    const QString ERASE = "Erase";
    const QString CROP = "Crop";
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
    Camera *camera;


    /*
     * EFFECTS: sets up toolbar; called by constructor
     */
    void SetupToolbar();
};
#endif // MAINWINDOW_H
