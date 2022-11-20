#include "fleetnamelist.h"

FleetNameList::FleetNameList(QWidget *parent)
    : QMainWindow{parent}
{
    fleetList = new QStringListModel(this);
}

void FleetNameList::Update(QListView *listView)
{
    listView->setModel(fleetList);
}

void FleetNameList::Clear(QListView *listView, QComboBox *box)
{
    QStringList st;
    fleetList->setStringList(st);
    listView->setModel(fleetList);
    box->clear();
}

void FleetNameList::LoadNameList(TreeItem* treeFleetName)
{
    //randomNameStringList.append(HelperFunctions::CreateStringList(&randomNameSectionString));
    //sequentialNameStringList.append(HelperFunctions::CreateStringList(&sequentialNameSectionString));
    fleetNameStringList.clear();
    if(treeFleetName->children.size()==0)
    {
        HelperFunctions::printLine("WARNING: fleet_names do not have any categories", HelperFunctions::printOption::YELLOW);
        return;
    }
    name_categories.clear();
    for(auto nameType:treeFleetName->children)
    {
        QStringList fleetNameTypeList;
        name_categories.push_back(nameType->key);
        if(nameType->children.size()==0) HelperFunctions::printLine("WARNING: \'"+nameType->key+"\' has no names", HelperFunctions::printOption::YELLOW);
        for(auto fleet:nameType->children)
            fleetNameTypeList.push_back(fleet->key);
        fleetNameStringList.push_back(fleetNameTypeList);
    }
}

void FleetNameList::LoadNameCategories(QComboBox *box)
{
    box->clear();
    for(auto cat : name_categories)
        box->addItem(cat);
}

void FleetNameList::LoadNames(int index, QListView *listView)
{
    if(index>=0)
    {
        fleetList->setStringList(fleetNameStringList[index]);
        Update(listView);
    }
}

void FleetNameList::AddCategory(QString name, TreeItem *treeFleetName)
{
    treeFleetName->InsertKey(name);
    fleetNameStringList.push_back(QStringList());
    name_categories.push_back(name);
}

void FleetNameList::EditNameList(int index, std::vector<QString> *names, TreeItem *treeFleetName)
{
    QString cat = name_categories[index];
    for(auto name:*names)
    {
        fleetNameStringList[index].push_back(name);
        (*treeFleetName)[cat].InsertKey(name);
    }
}

void FleetNameList::EditName(int index, int nameIndex, QString name, TreeItem *treeFleetName)
{
    QString cat = name_categories[index];
    (*treeFleetName)[cat][nameIndex].key = name;
    fleetNameStringList[index][nameIndex] = name;
}
