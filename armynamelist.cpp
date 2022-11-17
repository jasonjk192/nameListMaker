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

ArmyNameSet ArmyNameList::GenerateArmyNameSet(TreeItem *treeNameSet)
{
    ArmyNameSet set;
    set.armyCategoryName = treeNameSet->key;
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


