#ifndef PALETTERETRIEVER_H
#define PALETTERETRIEVER_H

#include <QPixmap>
#include <QColor>
#include <QNetworkReply>
#include <QEventLoop>
#include <QJsonObject>

class PaletteRetriever : public QObject {
    Q_OBJECT
public:
    PaletteRetriever(QPixmap* img, QObject* parent = nullptr);

    void generatePalette();

public slots:
    void parseUploadResponse();
    void parseGetResponse();
    void getPaletteFromId();

signals:
    void uploadComplete();
    void paletteReadyForUse(QVector<QColor>);

private:
    QPixmap* img;
    QVector<QColor> palette;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QEventLoop *loop;
    QString uploadId;
    QString auth;

    void deleteImgRequest();
};

#endif // PALETTERETRIEVER_H
