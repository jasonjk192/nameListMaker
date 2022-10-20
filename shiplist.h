#ifndef SHIPLIST_H
#define SHIPLIST_H

#include "mainwindow.h"
#include "ui_mainwindow.h"

class shipList : public MainWindow
{
    Q_OBJECT
public:
    explicit shipList(MainWindow *parent = nullptr);

private:
    QStringListModel *shipNameListModel;


signals:

};

#endif // SHIPLIST_H
