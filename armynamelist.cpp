#include "armynamelist.h"

ArmyNameList::ArmyNameList(QWidget *parent)
    : QMainWindow{parent}
{
    armyList = new QStringListModel(this);
}

void ArmyNameList::Update(QListView *listView)
{
    listView->setModel(armyList);
}

void ArmyNameList::Clear(QListView *listView, QComboBox *box, QComboBox *box2)
{
    QStringList st;
    armyList->setStringList(st);
    listView->setModel(armyList);
    box->clear();
    box2->clear();
}

void ArmyNameList::LoadNameList(TreeItem* treeArmyName)
{
    armyNameSetList.clear();
    if(treeArmyName->children.size()==0)
    {
        HelperFunctions::printLine("WARNING: army_names do not have any categories", HelperFunctions::printOption::YELLOW);
        return;
    }
    categories.clear();
    for(auto armyType:treeArmyName->children)
    {
        ArmyNameSet nameSet = GenerateArmyNameSet(armyType);
        armyNameSetList.push_back(nameSet);
    }
}

void ArmyNameList::LoadCategories(QComboBox *box)
{
    box->clear();
    for(auto cat : armyNameSetList)
        box->addItem(cat.armyCategoryName);
}

void ArmyNameList::LoadCategoryNames(QComboBox *box)
{
    box->clear();
    for(auto name : armyNameSetList[selectedCategory].nameTypeCategories)
        box->addItem(name);
}

void ArmyNameList::LoadNames(int catIndex, int typeIndex, QListView *listView)
{
    if(catIndex>=0 && typeIndex>=0)
    {
        selectedCategory = catIndex;
        armyList->setStringList(armyNameSetList[catIndex].nameList[typeIndex]);
        Update(listView);
    }
}

void ArmyNameList::AddCategory(QString name, TreeItem *treeArmyName)
{
    TreeItem* treeNameSet = treeArmyName->InsertKey(name);
    armyNameSetList.push_back(GenerateArmyNameSet(treeNameSet));
}

void ArmyNameList::AddType(QString name, int catIndex, TreeItem *treeArmyName)
{
    armyNameSetList[catIndex].nameTypeCategories.push_back(name);
    armyNameSetList[catIndex].nameList.push_back(QStringList());
    (*treeArmyName)[catIndex].InsertKey(name);
}

void ArmyNameList::EditNameList(int catIndex, int typeIndex, std::vector<QString> *names, TreeItem *treeArmyName)
{
    QString cat = armyNameSetList[catIndex].nameTypeCategories[typeIndex];
    for(auto name:*names)
    {
        armyNameSetList[catIndex].nameList[typeIndex].push_back(name);
        (*treeArmyName)[catIndex][cat].InsertKey(name);
    }
}

void ArmyNameList::EditName(int catIndex, int typeIndex, int nameIndex, QString name, TreeItem *treeArmyName)
{
    QString cat = armyNameSetList[catIndex].nameTypeCategories[typeIndex];
    (*treeArmyName)[catIndex][cat][nameIndex].key = name;
    armyNameSetList[catIndex].nameList[typeIndex][nameIndex] = name;
}

void ArmyNameList::EditCategory(QString name, int catIndex, TreeItem *treeArmyName)
{
    armyNameSetList[catIndex].armyCategoryName = name;
    (*treeArmyName)[catIndex].key = name;
}

void ArmyNameList::EditType(QString name, int catIndex, int typeIndex, TreeItem *treeArmyName)
{
     armyNameSetList[catIndex].nameTypeCategories[typeIndex] = name;
    (*treeArmyName)[catIndex][typeIndex].key = name;
}

void ArmyNameList::RemoveCategory(int catIndex, TreeItem *treeArmyName)
{
    if(categories.size()==1)
    {
        HelperFunctions::printLine("WARNING: Cannot remove last category",HelperFunctions::printOption::YELLOW);
        return;
    }
    armyNameSetList.erase(armyNameSetList.begin()+catIndex);
    (*treeArmyName)[catIndex].RemoveKey();
}

void ArmyNameList::RemoveType(int catIndex, int typeIndex, TreeItem *treeArmyName)
{
    armyNameSetList[catIndex].nameTypeCategories.erase(armyNameSetList[catIndex].nameTypeCategories.begin()+typeIndex);
    (*treeArmyName)[catIndex][typeIndex].RemoveKey();
}

ArmyNameSet ArmyNameList::GenerateArmyNameSet(TreeItem *treeNameSet)
{
    ArmyNameSet set;
    set.armyCategoryName = treeNameSet->key;
    if(treeNameSet->children.size()==0)
    {
        set.nameTypeCategories.push_back("random_names");
        set.nameTypeCategories.push_back("sequential_name");
        set.nameList.push_back(QStringList());
        set.nameList.push_back(QStringList());
    }
    for(auto nameType:treeNameSet->children)
    {
        set.nameTypeCategories.push_back(nameType->key);
        QStringList names;
        for(auto name:nameType->children)
            names.append(name->key);
        set.nameList.push_back(names);
    }
    return set;
}


