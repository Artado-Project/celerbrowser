#ifndef MENU_H
#define MENU_H

#include <QObject>
#include <QQmlEngine>
#include <QWidget>

class menu : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit menu(QObject *parent = nullptr);

signals:

};

#endif // MENU_H
