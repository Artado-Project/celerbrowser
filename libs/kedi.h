#ifndef KEDI_H
#define KEDI_H

#include <QTextBrowser>
#include <QRegularExpressionMatchIterator>
#include <QFile>
#include "httpreq.h"

class kedi : public QTextBrowser
{
    Q_OBJECT

public:
    explicit kedi(QWidget *parent = nullptr);

    void setHtml(const QString &html){
        //CSS Apply
        QString processedHtml = processHtml(html);
        QTextBrowser::setHtml(processedHtml);
        applyExternalStyles();
    }

private slots:
    void onAnchorClicked(const QUrl &url) {
        req->sendGetRequest(url);
    }

    void onRequestFinished(const QString &htmlContent) {
        this->setHtml(htmlContent);
    }

    void onRequestError(const QString &errorString) {
        this->setText("Error loading page: " + errorString);
    }

private:
    httpreq *req;

    QStringList cssFiles;

    //Edits the CSS links
    QString processHtml(const QString &html){
        QRegularExpression re("<link\\s+href=\"([^\"]+)\"\\s+rel=\"stylesheet\"[^>]*>");
        QRegularExpressionMatchIterator i = re.globalMatch(html);
        while (i.hasNext()) {
            QRegularExpressionMatch match = i.next();
            QString cssPath = match.captured(1);
            cssFiles.append(cssPath);
        }
        return html;
    }

    void applyExternalStyles() {
        foreach (const QString &cssFile, cssFiles) {
            loadAndApplyCSS(cssFile);
        }
    }

    //Gets the CSS Files
    void loadAndApplyCSS(const QString &cssPath) {
        if (cssPath.startsWith("http://") || cssPath.startsWith("https://")) {
            // Load CSS from the network
            QNetworkAccessManager *manager = new QNetworkAccessManager(this);
            connect(manager, &QNetworkAccessManager::finished, this, &kedi::onCssLoaded);
            manager->get(QNetworkRequest(QUrl(cssPath)));
        } else {
            QString newpath = cssPath + this->document()->baseUrl().toString();
            QNetworkAccessManager *manager = new QNetworkAccessManager(this);
            connect(manager, &QNetworkAccessManager::finished, this, &kedi::onCssLoaded);
            manager->get(QNetworkRequest(QUrl(newpath)));
        }
    }

    void onCssLoaded(QNetworkReply *reply) {
        if (reply->error() == QNetworkReply::NoError) {
            QString cssContent = reply->readAll();
            applyCSS(cssContent);
        }
        reply->deleteLater();
    }

    void applyCSS(const QString &cssContent) {
        QStringList rules = cssContent.split("}", Qt::SkipEmptyParts);
        for (const QString &rule : rules) {
            QStringList parts = rule.split("{", Qt::SkipEmptyParts);
            if (parts.size() == 2) {
                QString selector = parts[0].trimmed();
                QString styles = parts[1].trimmed();
                applyStylesToSelector(selector, styles);
            }
        }
    }

    void applyStylesToSelector(const QString &selector, const QString &styles) {
        QTextDocument *doc = this->document();
        QTextCursor cursor(doc);

        // Simplified example: applying inline styles directly to elements matching the selector
        cursor.beginEditBlock();
        cursor.select(QTextCursor::Document);
        QString html = cursor.selectedText();
        html.replace(selector, QString("<span style=\"%1\">").arg(styles) + selector + "</span>");
        cursor.insertHtml(html);
        cursor.endEditBlock();
    }
};
#endif // KEDI_H
