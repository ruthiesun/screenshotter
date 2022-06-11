#include "colourpicker.h"
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <iostream>
#include <QUrlQuery>

ColourPicker::ColourPicker() {
    buffer = QByteArray();
    netManager = new QNetworkAccessManager();
    reqPalette();
}

void ColourPicker::readPalette() {
    buffer.append(netReply->readAll());
    std::cout << "read soemthing" << std::endl;
}

void ColourPicker::finishReading() {
    std::cout << "done requesting stuff" << std::endl;
    if(netReply->error() != QNetworkReply::NoError){
        qDebug() << "Error : " << netReply->errorString();
        //QMessageBox::warning(this,"Error",QString("Request[Error] : %1").arg(netReply->errorString()));
    } else {
        //CONVERT THE DATA FROM A JSON DOC TO A JSON OBJECT
        QJsonObject jsonInfo = QJsonDocument::fromJson(buffer).object();
        //SET USERNAME
        QString array = jsonInfo.value("result").toString();
        std::cout << array.toStdString() << std::endl;
        std::cout << "in else bloc" << std::endl;
    }
    std::cout << "wow no bugs" << std::endl;
}

void ColourPicker::reqPalette() {
    QUrl url("http://dog-api.kinduff.com");//("http://colormind.io/api/");
    //QUrlQuery query{url};
    //query.addQueryItem("model","default");
    //url.setQuery(query);

    QNetworkRequest req{url};
    netReply = netManager->get(req);

    QObject::connect(netReply, &QNetworkReply::readyRead,
                     this, &ColourPicker::readPalette);
    QObject::connect(netReply, &QNetworkReply::finished,
                     this, &ColourPicker::finishReading);

    std::cout << "requested" << std::endl;
}
