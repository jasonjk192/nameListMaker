#include "shiplist.h"

shipList::shipList(MainWindow *parent) : MainWindow(parent)
{
    shipNameListModel = new QStringListModel(this);
    QStringList list;
    list.append("ONE");
    list.append("TWO");
    shipNameListModel->setStringList(list);
    ui->listView_ship->setModel(shipNameListModel);

}
