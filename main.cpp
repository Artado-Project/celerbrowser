#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QWebEnginePage>
#include <QWebEngineNavigationRequest>
#include <QDir>
#include "celerrequestinterceptor.h"
#include <QWebEngineUrlScheme>
#include <QWebEngineProfile>


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_UseSoftwareOpenGL, false);
    qputenv("QTWEBENGINE_CHROMIUM_FLAGS", "--enable-zero-copy");

    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "celerbrowser_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.show();
    return a.exec();
}
