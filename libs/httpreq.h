#ifndef HTTPREQ_H
#define HTTPREQ_H

#include <QObject>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>

class httpreq : public QObject {
    Q_OBJECT

public:
    explicit httpreq(QObject *parent = nullptr);
    void sendGetRequest(const QUrl &url);

signals:
    void requestFinished(const QString &htmlContent);
    void requestError(const QString &errorString);

private slots:
    void onRequestFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager *networkManager;
};

#endif // HTTPREQ_H

