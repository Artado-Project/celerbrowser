#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDebug>

QUrl url;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->bar->setText("celer://newtab");
    QPushButton *search = MainWindow::findChild<QPushButton *>("search");
    connect(ui->search, SIGNAL(released()), this, SLOT(Search()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Search() {
    QLineEdit *bar = MainWindow::findChild<QLineEdit *>("bar");
    QTextBrowser *browser = MainWindow::findChild<QTextBrowser *>("kedi");

    //Set up manager and URL for HTTP req
    QNetworkAccessManager manager;
    QUrl url(bar->text());

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
