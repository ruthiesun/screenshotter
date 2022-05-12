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

public slots:

signals:

private:
    QWidget* centralWidget;
    CollectionScroller* scroller;
    QToolBar* toolbar;
    ScreenshotEditor* editor;
    QHBoxLayout* mainLayout;
    QGridLayout* editAreaLayout;

    /*
     * EFFECTS: sets up widget that displays a view of the user's collection of screenshots
     *          called by constructor
     */
    void SetupScrollbar();

    /*
     * EFFECTS: sets up toolbar that allows user to modify a screenshot
     *          called by constructor
     */
    void SetupToolbar();

    /*
     * EFFECTS: sets up widget that displays a view of one screenshot
     *          called by constructor
     */
    void SetupEditor();

    /*
     * EFFECTS: adds img to the user's collection
     */
    void AddScreenshot(QPixmap* img);
};
#endif // MAINWINDOW_H
