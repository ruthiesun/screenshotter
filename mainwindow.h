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
    /*
     * EFFECTS:     constructor
     */
    MainWindow(QWidget *parent = nullptr);

    /*
     * EFFECTS:     destructor
     */
    ~MainWindow();

    /*
     * EFFECTS:     sets default size to full screen
     */
    QSize sizeHint() const override;

public slots:
    /*
     * REQUIRES:    action was signalled from the toolbar
     * EFFECTS:     responds to the button pressed on the toolbar:
     *              if draw, switches editor mode to drawing
     *              if erase, switches editor mode to erasing
     *              if save to file, opens a dialog that prompts user to save the image that is currently displayed
     *              if new copy, duplicates original version of the image that is currently displayed and stores the duplicate as a child
     *              if delete, deletes the image that is currently displayed and any children
     *              if new screenshot, opens camera dialog that allows user to take a screenshot
     */
    void ParseToolbarSignal(QAction* action);

    /*
     * REQUIRES:    img is not null
     * EFFECTS:     adds img to the user's collection
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
     * EFFECTS:     sets up toolbar
     *              called by constructor
     */
    void SetupToolbar();

    /*
     * EFFECTS:     sets up the ui
     *              called by the constructor
     */
    void Setup();
};
#endif // MAINWINDOW_H
