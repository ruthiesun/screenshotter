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
     *              also sets up widget appearance
     */
    explicit Camera(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    QPoint* getPrevPos();

public slots:
    /*
     * EFFECTS:     eats some ice cream and starts going to the gym
     *              also saves the current position of the dialog
     */
    void handleRejection();

signals:
    void snapped(QPixmap* img);

protected:
    /*
     * EFFECTS:     deletes the previous position; saves the current position of the dialog
     */
    void closeEvent(QCloseEvent *event);

private:
    QPushButton *button;
    QPoint *prevPos;

    /*
     * REQUIRES:    dialog is in focus
     * EFFECTS:     takes a picture of contents underneath dialog screen
     *              emits a Snapped signal with that picture
     */
    void takePic();

    /*
     * MODIFIES:    this
     * EFFECTS:     sets up the ui
     *              called by the constructor
     */
    void setup();
};

#endif // CAMERA_H
