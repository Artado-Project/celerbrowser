#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWebEngineView>
#include <QRegularExpression>
#include <QTabWidget>
#include <QMap>
#include <QFrame>
#include <QPushButton>
#include <QLineEdit>
#include <QMenu>
#include <QWebEngineUrlScheme>
#include <QWebEngineProfile>
#include <QFile>
#include <QTextStream>
#include <QWebEnginePage>
#include <QWebEngineNavigationRequest>
#include <QDir>
#include <QStandardPaths>
#include "celerrequestinterceptor.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tabWidget = new QTabWidget();

    //Settings for celer:// routing
    QWebEngineUrlScheme celerScheme("celer");
    celerScheme.setSyntax(QWebEngineUrlScheme::Syntax::HostAndPort);
    celerScheme.setDefaultPort(80);  // Optional, depending on if you use a default port
    celerScheme.setFlags(QWebEngineUrlScheme::SecureScheme | QWebEngineUrlScheme::LocalScheme);
    QWebEngineUrlScheme::registerScheme(celerScheme);

    //Settings for performance
    QWebEngineProfile *profile = QWebEngineProfile::defaultProfile();
    profile->setPersistentCookiesPolicy(QWebEngineProfile::ForcePersistentCookies);
    profile->setHttpCacheType(QWebEngineProfile::DiskHttpCache);
    profile->setHttpCacheMaximumSize(1024 * 1024 * 100);
    profile->setCachePath(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/cache");
    profile->setPersistentStoragePath(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/storage");

    //Set the Interceptor
    CelerRequestInterceptor *interceptor = new CelerRequestInterceptor();
    QWebEngineProfile::defaultProfile()->setUrlRequestInterceptor(interceptor);

    qDebug() << "Cache path set to: " << profile->cachePath();
    qDebug() << "Persistent storage path set to: " << profile->persistentStoragePath();
    qDebug() << "Max cache size set to: " << profile->httpCacheMaximumSize();

    previousTabIndex = 0;

    newTab();
}

void MainWindow::onUrlChanged(const QUrl &url)
{
    // Get the current tab widget
    QWidget *currentTab = ui->tabWidget->currentWidget();

    //Get the frame
    QFrame *frame = currentTab->findChild<QFrame*>("tabFrame");

    //celer:// routing
    if(url.scheme() == "celer"){
        // Find the search bar within the current tab
        QLineEdit *bar = frame->findChild<QLineEdit*>();
        bar->setText("");
        handleNavigation(url);
    }
    else{
        // Find the search bar within the current tab
        QLineEdit *bar = frame->findChild<QLineEdit*>();
        bar->setText(url.toString());
    }
}

void MainWindow::Search()
{
    // Get the current tab widget
    QWidget *currentTab = ui->tabWidget->currentWidget();

    //Get the frame
    QFrame *frame = currentTab->findChild<QFrame*>("tabFrame");

    // Find the search bar within the current tab
    QLineEdit *bar = frame->findChild<QLineEdit*>();

    QString input = bar->text();

    static QRegularExpression urlRegex(R"(\b(?:https?://)?(?:www\.)?(?:[a-zA-Z0-9-]+\.)+[a-zA-Z]{2,6}\b)");

    // Find the QWebEngineView within the current tab
    QWebEngineView *currentView = currentTab->findChild<QWebEngineView*>();

    if (urlRegex.match(input).hasMatch()) {
        currentView->setUrl(QUrl::fromUserInput(input));
    } else {
        currentView->setUrl(QUrl("https://www.artadosearch.com/search?i=" + QUrl::toPercentEncoding(input)));
    }
}

void MainWindow::newTab(){
    QWidget *tab = new QWidget();
    QVBoxLayout *tabLayout = new QVBoxLayout(tab);
    tabLayout->setContentsMargins(0, 0, 0, 0);

    // Frame containing the navigation and search controls
    QFrame *frame = new QFrame(tab);
    frame->setObjectName("tabFrame");
    frame->setMaximumHeight(41);
    frame->setFrameShape(QFrame::StyledPanel);
    frame->setFrameShadow(QFrame::Raised);

    //Create a web view
    QWebEngineView *view = new QWebEngineView();

    // Back button
    QPushButton *backButton = new QPushButton("<", frame);
    backButton->setGeometry(10, 10, 31, 24);

    // Next button
    QPushButton *nextButton = new QPushButton(">", frame);
    nextButton->setGeometry(40, 10, 31, 24);

    // Reload button
    QPushButton *reloadButton = new QPushButton("R", frame);
    reloadButton->setGeometry(80, 10, 31, 24);

    // Stop button
    QPushButton *stopButton = new QPushButton("S", frame);
    stopButton->setGeometry(110, 10, 31, 24);

    // New tab button
    QPushButton *newTabButton = new QPushButton("+", frame);
    newTabButton->setGeometry(160, 10, 31, 24);

    // Search bar
    QLineEdit *searchBar = new QLineEdit(frame);
    searchBar->setGeometry(300, 10, 531, 24);
    searchBar->setStyleSheet("border-radius: 5px;");
    searchBar->setPlaceholderText("Search or enter an address");

    // Search button
    QPushButton *searchButton = new QPushButton("Search", frame);
    searchButton->setGeometry(830, 10, 71, 24);

    //Setup Menu
    // Create the menu button
    QPushButton *menuButton = new QPushButton("☰", frame);
    menuButton->setFixedSize(40, 25);
    menuButton->setStyleSheet("font-size: 10px;");
    menuButton->setGeometry(910, 10, 71, 24);

    // Create the menu and actions
    QMenu *menu = new QMenu(this);
    QAction *settingsAction = new QAction("Settings", this);
    QAction *historyAction = new QAction("History", this);
    QAction *downloadsAction = new QAction("Downloads", this);

    connect(settingsAction, &QAction::triggered, this, &MainWindow::openSettings);
    connect(historyAction, &QAction::triggered, this, &MainWindow::openHistory);
    connect(downloadsAction, &QAction::triggered, this, &MainWindow::openDownloads);

    menu->addAction(settingsAction);
    menu->addAction(historyAction);
    menu->addAction(downloadsAction);

    // Attach menu to the button
    menuButton->setMenu(menu);

    // Add frame to Tab 1 layout
    tabLayout->addWidget(frame);

    // QWebEngineView as the browser view
    tabLayout->addWidget(view);

    // Add Tab to the Tab Widget
    int newIndex = ui->tabWidget->addTab(tab, "New Tab");

    //Switch to new tab
    ui->tabWidget->setCurrentIndex(newIndex);

    handleNavigation(QUrl("celer://newtab"));

    // Connect signals
    connect(backButton, &QPushButton::clicked, view, &QWebEngineView::back);
    connect(nextButton, &QPushButton::clicked, view, &QWebEngineView::forward);
    connect(reloadButton, &QPushButton::clicked, view, &QWebEngineView::reload);
    connect(stopButton, &QPushButton::clicked, view, &QWebEngineView::stop);
    connect(newTabButton, &QPushButton::clicked, this, &MainWindow::newTab);
    connect(searchButton, &QPushButton::clicked, this, &MainWindow::Search);
    //Change the address bar
    connect(view, &QWebEngineView::urlChanged, this, &MainWindow::onUrlChanged);
}

void MainWindow::handleNavigation(const QUrl &url) {
    // Map known routes to integer values
    static QHash<QString, int> routeMap {
        {"newtab", 1},
        {"settings", 2},
        {"history", 3}
    };

    int route = routeMap.value(url.host(), 0);

    // Get the current tab widget
    QWidget *currentTab = ui->tabWidget->currentWidget();

    // Find the QWebEngineView within the current tab
    QWebEngineView *currentView = currentTab->findChild<QWebEngineView*>();

    switch (route) {
        case 1: { // New Tab Page
            QString filePath = ":/resources/newtab.html";
            QFile file(filePath);
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(&file);
                QString htmlContent = in.readAll();
                currentView->setHtml(htmlContent, url);
                file.close();
            } else {
                qDebug() << "Failed to load newtab.html";
            }
            break;
        }

        case 2: { //settings page
            QString filePath = ":/resources/settings.html";
            QFile file(filePath);
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(&file);
                QString htmlContent = in.readAll();
                currentView->setHtml(htmlContent, url);
                file.close();
            } else {
                qDebug() << "Failed to load settings.html";
            }
            break;
        }

        case 3: { //history page
            QString filePath = ":/resources/history.html";
            QFile file(filePath);
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(&file);
                QString htmlContent = in.readAll();
                currentView->setHtml(htmlContent, url);
                file.close();
            } else {
                qDebug() << "Failed to load history.html";
            }
            break;
        }

        default:
            // For undefined "celer" routes
            qDebug() << "Unknown celer route: " << url.host();
            currentView->setHtml("<html><body><h1>Page Not Found</h1></body></html>", url);
            break;
    }
}


// Slots for the actions
void MainWindow::openSettings() {
    // Your code to open settings
}

void MainWindow::openHistory() {
    // Your code to open history
}

void MainWindow::openDownloads() {
    // Your code to open downloads
}

MainWindow::~MainWindow()
{
    delete ui;
}
