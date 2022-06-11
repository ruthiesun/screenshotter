#ifndef COLOURPICKER_H
#define COLOURPICKER_H

#include <QDialog>
#include <QWidget>
#include <QNetworkAccessManager>

class ColourPicker : public QDialog
{
    Q_OBJECT
public:
    /*
     * EFFECTS:     !!!
     */
    ColourPicker();

public slots:
    /*
     * EFFECTS:     !!!
     */
    void readPalette();

    /*
     * EFFECTS:     !!!
     */
    void finishReading();

private:
    QNetworkAccessManager *netManager;
    QNetworkReply *netReply;
    QColor *colours[5];
    QPixmap *img;
    QByteArray buffer;

    /*
     * EFFECTS:     makes request to Colormind with img and stores result in array of colours
     */
    void reqPalette();


    //QColor toQColor();
};

#endif // COLOURPICKER_H
