#ifndef PALETTERETRIEVER_H
#define PALETTERETRIEVER_H

#include <QPixmap>
#include <QColor>
#include <QNetworkReply>
#include <QJsonObject>

/*
 * menu widget that displays a selection of pen colours
 */
class PaletteRetriever : public QObject {
    Q_OBJECT
public:
    /*
     * EFFECTS:     constructor
     */
    PaletteRetriever(QPixmap* img, QObject* parent = nullptr);

    /*
     * EFFECTS:     makes upload request to Imagga with img
     */
    void generatePalette();

public slots:
    /*
     * REQUIRES:    reply has received all data from an upload post request to Imagga
     * MODIDFIES:   this
     * EFFECTS:     parses JSON data in reply to obtain the image id and stores this into uploadId
     *              emits uploadComplete signal when done
     */
    void parseUploadResponse();

    /*
     * REQUIRES:    uploadId is the id of an image stored on Imagga
     * EFFECTS:     makes a get request for colour extraction to Imagga with uploadId
     */
    void getPaletteFromId();

    /*
     * REQUIRES:    reply has received all data from a colours get request to Imagga
     * MODIFIES:    this
     * EFFECTS:     parses JSON data in reply
     *              generates a list of QColors from the data, stores it in palette, and emits a paletteReadyForUse signal with this list
     */
    void parseGetResponse();

signals:
    void uploadComplete();
    void paletteReadyForUse(QVector<QColor>);

private:
    QPixmap* img;
    QVector<QColor> palette;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QString uploadId;
    QString auth;

    /*
     * EFFECTS:     makes request to delete the image with uploadId off the Imagga servers
     */
    void deleteImgRequest();
};

#endif // PALETTERETRIEVER_H
