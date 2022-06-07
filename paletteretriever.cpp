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
#include <QJsonArray>

PaletteRetriever::PaletteRetriever(QPixmap* img, QObject* parent) : QObject(parent) {
    this->img = img;
    manager = new QNetworkAccessManager(this);
    auth = "my cool auth";
}

void PaletteRetriever::generatePalette() {
    QBuffer buffer(this);
    buffer.open(QIODevice::WriteOnly);
    img->save(&buffer, "PNG");
    auto const encoded = buffer.data().toBase64();

    QString imgIn64 = "data:image/png;base64," + QString(encoded.constData());
    QString body = "image_base64=\"" + imgIn64 + "\"\r\n";
    QNetworkRequest request;
    QUrl url("https://api.imagga.com/v2/uploads");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "multipart/form-data");
    request.setUrl(url);
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

    QBuffer *pBuffer = new QBuffer(manager);
    pBuffer->setData(data);
    /* END */

    QHttpPart textPart;
    textPart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image_base64"));
    textPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"image_base64\""));
    textPart.setRawHeader("image_base64", "image_base64");
    textPart.setBody("image_base64");

    reply = manager->post(request, pBuffer);

    QObject::connect(reply, &QNetworkReply::finished,
                     this, &PaletteRetriever::parseUploadResponse);
    QObject::connect(this, &PaletteRetriever::uploadComplete,
                     this, &PaletteRetriever::getPaletteFromId);

    /*
    connect(reply, &QNetworkReply::errorOccurred,
            this, &MyClass::slotError);
    connect(reply, &QNetworkReply::sslErrors,
            this, &MyClass::slotSslErrors);*/
}

void PaletteRetriever::getPaletteFromId() {
    std::cout << uploadId.toStdString() << std::endl;
    QNetworkRequest request;
    QUrl url("https://api.imagga.com/v2/colors");

    QUrlQuery query;
    query.addQueryItem("image_upload_id",uploadId);
    query.addQueryItem("extract_object_colors","0");

    url.setQuery(query);

    request.setUrl(url);
    request.setRawHeader("Authorization", auth.toLocal8Bit());

    reply = manager->get(request);

    QObject::connect(reply, &QNetworkReply::finished,
                     this, &PaletteRetriever::parseGetResponse);
}

void PaletteRetriever::parseUploadResponse() {
    QByteArray result = reply->readAll();
    QJsonObject jsonReply = QJsonDocument::fromJson(result).object();
    QJsonObject jsonResult = jsonReply["result"].toObject();
    uploadId = jsonResult["upload_id"].toString();
    emit uploadComplete();
}

void PaletteRetriever::parseGetResponse() {
    QByteArray result = reply->readAll();
    std::cout << result.toStdString() << std::endl;
    QJsonObject jsonReply = QJsonDocument::fromJson(result).object();
    QJsonObject jsonResult = jsonReply["result"].toObject();
    QJsonObject jsonColors = jsonResult["colors"].toObject();
    QJsonArray jsonImageColors = jsonColors["image_colors"].toArray();

    for (QJsonArray::const_iterator j = jsonImageColors.constBegin(); j != jsonImageColors.constEnd(); j++) {

        QJsonObject jsonCurrColor = j->toObject();
        int r = jsonCurrColor.value("r").toInt();
        int g = jsonCurrColor.value("g").toInt();
        int b = jsonCurrColor.value("b").toInt();

        palette.append(QColor(r,g,b));
    }

    emit paletteReadyForUse(palette);

    deleteImgRequest();
}

void PaletteRetriever::deleteImgRequest() {
    //delete img from imagga
    //delete this
}
