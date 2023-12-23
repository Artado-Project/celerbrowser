#include "mainwindow.h"
#include "httpreq.h"
#include "./ui_mainwindow.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDebug>

httpreq::httpreq(QUrl url, QObject *parent) : QObject(parent), m_url(url) {
    QNetworkAccessManager manager;
    kedi *browser = parent->findChild<kedi *>("kedi");

    //Send HTTP req
    QNetworkRequest req(url);
    QNetworkReply *reply = manager.get(req);
    QEventLoop event;

    //Wait for reply
    QObject::connect(reply, &QNetworkReply::finished, &event, &QEventLoop::quit);
    event.exec();

    if(reply->error() == QNetworkReply::NoError){
        //Read the response data
        QByteArray response = reply->readAll();

        // Convert the data to a QString
        QString html = QString::fromUtf8(response);

        browser->setHtml(html);
    }
    else{
        browser->setMarkdown("something bad happened");
    }
}
