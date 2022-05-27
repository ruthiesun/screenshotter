#ifndef CAMERA_H
#define CAMERA_H

#include <QDialog>
#include <QObject>
#include <QPushButton>

class Camera : public QDialog
{
    Q_OBJECT
public:
    explicit Camera(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

public slots:

signals:
    void Snapped(QPixmap* img);

protected:

private:
    QPushButton *button;

    /*
     * EFFECTS: takes a picture of contents underneath entire dialog screen
     */
    void TakePic();
};

#endif // CAMERA_H
