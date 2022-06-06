#ifndef PALETTERETRIEVER_H
#define PALETTERETRIEVER_H

#include <QPixmap>
#include <QColor>
#include <QNetworkReply>
#include <QEventLoop>

class PaletteRetriever : public QObject {
    Q_OBJECT
public:
    PaletteRetriever(QPixmap* img, QObject* parent = nullptr);

    QColor* generatePalette();

public slots:
    void parseResponse();

private:
    QPixmap* img;
    QColor palette [5];
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QByteArray *buffer;
    QEventLoop *loop;
    QHttpMultiPart *multiPart;

};

#endif // PALETTERETRIEVER_H
