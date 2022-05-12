#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QToolButton>
#include "collectionscroller.h"
#include "screenshoteditor.h"

/*
 * class representing the application's window
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    int scrollbarWidth;

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
     * EFFECTS: updates the image displayed in the editor with img
     */
    void UpdateEditor(QPixmap* img);

    /*
     * REQUIRES: action was signalled from the toolbar
     * EFFECTS: determines the source of the signal begins an appropriate response
     */
    void ParseToolbarSignal(QAction* action);

signals:

private:
    QWidget* centralWidget;
    CollectionScroller* scroller;
    QToolBar* toolbar;
    ScreenshotEditor* editor;
    QHBoxLayout* mainLayout;
    QGridLayout* editAreaLayout;

    /*
     * EFFECTS: sets up toolbar that allows user to modify a screenshot
     *          called by constructor
     */
    void SetupToolbar();
};
#endif // MAINWINDOW_H
