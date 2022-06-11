#ifndef CAMERA_H
#define CAMERA_H

#include <QDialog>
#include <QObject>
#include <QPushButton>

/*
 * translucent window in which users can take screenshots
 */
class Camera : public QDialog {
    Q_OBJECT
public:
    /*
     * EFFECTS:     constructor
     */
    explicit Camera(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    /*
     * EFFECTS:     returns most recent top-left position (prevPos) of this dialog
     *              if this is the first time opening the dialog, returns nullptr
     */
    QPoint* getPrevPos();

public slots:
    /*
     * REQUIRES:    called when user rejects (i.e. closes) the dialog
     * MODIFIES:    this
     * EFFECTS:     saves the current position of the dialog into prevPos
     */
    void handleRejection();

signals:
    void snapped(QPixmap* img);

protected:
    /*
     * MODIFIES:    this
     * EFFECTS:     saves the current position of the dialog into prevPos
     *              if prevPos was not null before this was called, deletes the previous point object
     */
    void closeEvent(QCloseEvent *event);

private:
    QPushButton *button;
    QPoint *prevPos;

    /*
     * REQUIRES:    this dialog is in focus
     * EFFECTS:     takes a screenshot of contents underneath dialog screen
     *              emits a snapped signal with that screenshot
     */
    void takePic();

    /*
     * MODIFIES:    this
     * EFFECTS:     sets up the UI
     *              called by the constructor
     */
    void setup();
};

#endif // CAMERA_H
