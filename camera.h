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

public slots:

signals:
    void snapped(QPixmap* img);

protected:

private:
    QPushButton *button;

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
