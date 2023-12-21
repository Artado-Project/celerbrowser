#include "mainwindow.h"
#include "httpreq.h"
#include "./ui_mainwindow.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDebug>

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

    //Set up for HTTP req
    QUrl url(bar->text());

    httpreq *req = new httpreq(url, this);

    delete req;
    req = nullptr;
}
