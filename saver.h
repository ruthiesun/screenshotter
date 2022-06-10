#ifndef SAVER_H
#define SAVER_H

#include <QObject>
#include "canvas.h"
#include <QClipboard>

/*
 * performs image saving/clipboard tasks
 */
class Saver : public QObject {
    Q_OBJECT
public:
    /*
     * EFFECTS:     constructor
     */
    explicit Saver(QObject *parent = nullptr);

    /*
     * REQUIRES:    img is not null
     * MODIFIES:    img
     * EFFECTS:     copies img to clipboard
     *              deletes img before returning
     */
    void imgToClipboard(QPixmap* img);

    /*
     * REQUIRES:    img is not null
     * MODIFIES:    img
     * EFFECTS:     opens a dialog that allows user to save img
     *              deletes img before returning
     *              if no file name was supplied, does not save the image and does not delete img
     */
    void saveImg(QPixmap* img);

    /*
     * REQUIRES:    canvas is not null
     * MODIFIES:    canvas
     * EFFECTS:     returns the contents of canvas (background and drawings), compressed into a pixmap
     *              clears selection of canvas
     */
    QPixmap* getCanvasAsPixmap(Canvas* canvas);
signals:

private:
    QClipboard* clipboard;

};

#endif // SAVER_H
