#ifndef CELERREQUESTINTERCEPTOR_H
#define CELERREQUESTINTERCEPTOR_H

#include <QMainWindow>
#include <QObject>
#include <QWebEngineUrlRequestInterceptor>
#include <QWidget>

class CelerRequestInterceptor : public QWebEngineUrlRequestInterceptor
{
public:
    CelerRequestInterceptor();
    void interceptRequest(QWebEngineUrlRequestInfo &info) override {
        if (info.requestUrl().scheme() == "celer") {
            QString url = info.requestUrl().toString().remove("celer://").remove("/");
            // Map `celer://` URLs to the local file system or resource paths
            QString localPath = "qrc:/resources/" + url;
            info.redirect(QUrl(localPath));
        }
    }
};

#endif // CELERREQUESTINTERCEPTOR_H
