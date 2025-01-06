#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebEngineView>
#include <QLineEdit>
#include <QWebEnginePage>
#include <QWebEngineNavigationRequest>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void Search();
    void onUrlChanged(const QUrl &url);
    void newTab();
    void openSettings();
    void openHistory();
    void openDownloads();
private:
    Ui::MainWindow *ui;
    QTabWidget *tabWidget;
    int previousTabIndex;
    void handleNavigation(const QUrl &url);
};
#endif // MAINWINDOW_H
