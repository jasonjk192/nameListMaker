#include "shipnamelist.h"

ShipNameList::ShipNameList(QMainWindow *parent) : QMainWindow(parent)
{
    shipList = new QStringListModel(this);
}

void ShipNameList::Update(QListView* listView)
{
    listView->setModel(shipList);
}

void ShipNameList::LoadNameList(TreeItem* treeShipName)
{
    shipCategoryBodyList.clear();
    if(treeShipName->children.size()==0)
    {
        HelperFunctions::printLine("WARNING: ship_names do not have any categories", "yellow");
        return;
    }
    categories.clear();
    for(auto shipType:treeShipName->children)
    {
        QStringList shipClassList;
        categories.push_back(shipType->key);
        if(shipType->children.size()==0) HelperFunctions::printLine("WARNING: ship category\'"+shipType->key+"\' has no names", "yellow");
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
