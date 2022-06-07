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
#include "colourselector.h"

/*
 * class representing the application's window
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    static const int scrollerRatioValue = 1;
    static const int editorRatioValue = 5;

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
     *              if copy, copies image that is currently displayed to clipboard
     *              if new screenshot, opens camera dialog that allows user to take a screenshot
     */
    void parseToolbarSignal(QAction* action);

    /*
     * REQUIRES:    img is not null
     * MODIFIES:    this
     * EFFECTS:     adds img to the user's collection
     */
    void addScreenshot(QPixmap* img);

    /*
     * REQUIRES:    !!!
     * MODIFIES:    this
     * EFFECTS:     !!!
     */
    void makeNewCanvas();

signals:
    void canvasModeChanged(Canvas::Mode mode);

protected:
    /*
     * EFFECTS:     sets size to full screen when screen is restored
     */
    //void changeEvent(QEvent *event) override;

private:
    const QString DRAW = "Draw";
    const QString ERASE = "Erase";
    const QString CROP = "Crop";
    const QString NEW_COPY = "Duplicate original";
    const QString DELETE = "Delete";
    const QString SAVE_TO_FILE = "Save to file";
    const QString COPY = "Copy to clipboard";
    const QString NEW_SCREENSHOT = "Take new screenshot";

    QWidget* centralWidget;
    CollectionViewer* scroller;
    QToolBar* toolbar;
    ScreenshotEditor* editor;
    QHBoxLayout* mainLayout;
    QGridLayout* editAreaLayout;
    CollectionModel* model;
    Camera *camera;
    ColourSelector *colourMenu;

    /*
     * MODIFIES:    this
     * EFFECTS:     sets up toolbar
     *              called by constructor
     */
    void setupToolbar();

    /*
     * MODIFIES:    this
     * EFFECTS:     sets up the ui
     *              called by the constructor
     */
    void setup();
};
#endif // MAINWINDOW_H
