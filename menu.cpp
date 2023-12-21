#include "menu.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

menu::menu(QFrame *parent)
    : QFrame{parent}
    , ui(new Ui::menu)
{
    ui->setupUi(this);
}
