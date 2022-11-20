#include "shipnamelist.h"

ShipNameList::ShipNameList(QMainWindow *parent) : QMainWindow(parent)
{
    shipList = new QStringListModel(this);
}

void ShipNameList::Update(QListView* listView)
{
    listView->setModel(shipList);
}

void ShipNameList::Clear(QListView *listView, QComboBox *box)
{
    QStringList st;
    shipList->setStringList(st);
    listView->setModel(shipList);
    box->clear();
}

void ShipNameList::LoadNameList(TreeItem* treeShipName)
{
    shipCategoryBodyList.clear();
    if(treeShipName->children.size()==0)
    {
        HelperFunctions::printLine("WARNING: ship_names do not have any categories", HelperFunctions::printOption::YELLOW);
        return;
    }
    categories.clear();
    for(auto shipType:treeShipName->children)
    {
        QStringList shipClassList;
        categories.push_back(shipType->key);
        if(shipType->children.size()==0) HelperFunctions::printLine("WARNING: ship category\'"+shipType->key+"\' has no names", HelperFunctions::printOption::YELLOW);
        for(auto ship:shipType->children)
            shipClassList.push_back(ship->key);
        shipCategoryBodyList.push_back(shipClassList);
    }
}

void ShipNameList::LoadCategories(QComboBox* box)
{
    box->clear();
    for(auto cat : categories)
        box->addItem(cat);
}

void ShipNameList::LoadNames(int index, QListView *listView)
{
    if(index>=0)
    {
        shipList->setStringList(shipCategoryBodyList[index]);
        Update(listView);
    }
}

void ShipNameList::AddCategory(QString name, TreeItem *treeShipName)
{
    treeShipName->InsertKey(name);
    shipCategoryBodyList.push_back(QStringList());
    categories.push_back(name);
}

void ShipNameList::EditNameList(int index, std::vector<QString> *names, TreeItem *treeShipName)
{
    QString cat = categories[index];
    for(auto name:*names)
    {
        shipCategoryBodyList[index].push_back(name);
        (*treeShipName)[cat].InsertKey(name);
    }
}

void ShipNameList::EditName(int index, int nameIndex, QString name, TreeItem *treeShipName)
{
    QString cat = categories[index];
    (*treeShipName)[cat][nameIndex].key = name;
    shipCategoryBodyList[index][nameIndex] = name;
}
