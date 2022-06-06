#include "paletteretriever.h"
#include <QNetworkAccessManager>
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <iostream>
#include <QUrlQuery>
#include <QBuffer>
#include <QHttpMultiPart>
#include <QEventLoop>
#include <QFile>

PaletteRetriever::PaletteRetriever(QPixmap* img, QObject* parent) : QObject(parent) {
    this->img = img;
    buffer = new QByteArray();
}

QColor* PaletteRetriever::generatePalette() {
    manager = new QNetworkAccessManager(this);

    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);
    img->save(&buffer, "PNG");
    auto const encoded = buffer.data().toBase64();

    QString imgIn64 = "data:image/png;base64," + QString(encoded.constData());
    QString body = "image_base64=\"" + imgIn64 + "\"\r\n";
    QNetworkRequest request;
    QUrl url("https://api.imagga.com/v2/uploads");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "multipart/form-data");
    request.setUrl(url);
    QString auth("placeholder");
    request.setRawHeader("Authorization", auth.toLocal8Bit());

    /* The following code is modified from: https://stackoverflow.com/questions/35683785/qnetworkaccessmanager-how-to-send-multipart-patch-request
     * START
     */
    QString boundary("------------------------------------asdfyiuqwer762345");
    request.setRawHeader("Content-Type", QByteArray("multipart/form-data; boundary=").append(boundary.toUtf8()));

    QByteArray data;
    data.append("--" + boundary.toUtf8() + "\r\n");
    data.append("Content-Disposition: form-data; name=\"image_base64\"\r\n\n\n");
    /* additional 2 newlines before the body, in accordance with the docs: https://doc.qt.io/qt-5/qhttppart.html */
    data.append(body.toUtf8());
    data.append("--" + boundary.toUtf8() + "--\r\n");
    /* Final boundary has extra -- at end */

    QBuffer * pBuffer = new QBuffer(manager);
    pBuffer->setData(data);
    /* END */

    QHttpPart textPart;
    textPart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image_base64"));
    textPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"image_base64\""));
    textPart.setRawHeader("image_base64", "image_base64");
    textPart.setBody("image_base64");

    reply = manager->post(request, pBuffer);

    std::cout << "request sent" << std::endl;

    loop = new QEventLoop();

    QObject::connect(reply, &QNetworkReply::finished,
                     this, &PaletteRetriever::parseResponse);

    loop->exec();


    /*
    connect(reply, &QNetworkReply::errorOccurred,
            this, &MyClass::slotError);
    connect(reply, &QNetworkReply::sslErrors,
            this, &MyClass::slotSslErrors);*/

    return nullptr;
}

void PaletteRetriever::parseResponse() {
    std::cout << "request finished" << std::endl;
    QByteArray result = reply->readAll();
    std::string t = result.toStdString();
   // QJsonObject jsonReply = QJsonDocument::fromJson(result).object();
    //QString test = jsonReply.value("result").toString();
    std::cout << t << std::endl;
    delete multiPart;
    loop->exit();
}
