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
    //auto const encoded = buffer.data().toBase64();

    //QString imgIn64 = "data:image/png;base64," + QString(encoded.constData());
    QString imgIn64 = "image_base64=\"data:image/png;base64,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\"\r\n";
    QNetworkRequest request;
    QUrl url("https://api.imagga.com/v2/uploads");
    //request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    //request.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "multipart/form-data"); //"multipart/form-data");
    request.setUrl(url);
    QString auth("");
    request.setRawHeader("Authorization", auth.toLocal8Bit());

    //QUrlQuery urlQuery;
    //urlQuery.addQueryItem("image_base64", imgIn64);

    //std::cout << urlQuery.toString(QUrl::FullyEncoded).toUtf8().toStdString() << std::endl;

    //reply = manager->post(request, urlQuery.toString(QUrl::FullyEncoded).toUtf8());


    //multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QString boundary("------------------------------------asdfyiuqwer762345");
    request.setRawHeader("Content-Type", QByteArray("multipart/form-data; boundary=").append(boundary.toUtf8()));

    QByteArray data;
    data.append("--" + boundary.toUtf8() + "\r\n");
    data.append("Content-Disposition: form-data; name=\"image_base64\"\r\n\n\n");
    data.append(imgIn64.toUtf8());
    data.append("--" + boundary.toUtf8() + "--\r\n");
    /* Final boundary has extra -- at end */

    QBuffer * pBuffer = new QBuffer(manager);
    pBuffer->setData(data);


    QHttpPart textPart;
    textPart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image_base64"));
    textPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"image_base64\""));
    textPart.setRawHeader("image_base64", "image_base64");
    textPart.setBody("image_base64");
    //textPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"image_base64\""));
    //textPart.setBody("\""+ imgIn64.toLocal8Bit() + "\"");

/*
    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg"));
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"image\""));

    QFile *file = new QFile("image.jpeg");
    file->open(QIODevice::WriteOnly);
    if (!img->save(file)) {
        throw std::domain_error("ScreenshotEditor::UpdateView - failed to save image");
    }
    file->close();

    file->open(QIODevice::ReadOnly);
    imagePart.setBodyDevice(file);
    file->setParent(multiPart); // we cannot delete the file now, so delete it with the multiPart
*/
    //multiPart->append(textPart);
   // multiPart->append(imagePart);

    reply = manager->post(request, pBuffer);//multiPart);

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
