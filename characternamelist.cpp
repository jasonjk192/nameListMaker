#include "characternamelist.h"

CharacterNameList::CharacterNameList(QWidget *parent)
    : QMainWindow{parent}
{
    characterList = new QStringListModel(this);
}

void CharacterNameList::Update(QListView *listView)
{
    listView->setModel(characterList);
}

void CharacterNameList::Clear(QListView *listView, QComboBox *box, QComboBox *box2, QLineEdit *edit)
{
    QStringList st;
    characterList->setStringList(st);
    listView->setModel(characterList);
    box2->clear();
    box->clear();
    edit->clear();
}

void CharacterNameList::LoadNameList(TreeItem* treeCharacterName)
{
    characterNameSetList.clear();
    if(treeCharacterName->children.size()==0)
    {
        HelperFunctions::printLine("WARNING: character_names do not have any name sets", HelperFunctions::printOption::YELLOW);
        return;
    }
    for(auto characterSet:treeCharacterName->children)
    {
        CharacterNameSet nameSet = GenerateCharacterNameSet(characterSet);
        characterNameSetList.push_back(nameSet);
    }
}

void CharacterNameList::LoadNameCategories(QComboBox *box)
{
    box->clear();
    for(auto cat : characterNameSetList[selectedNameSet].nameSetCategories)
        box->addItem(cat);
}

void CharacterNameList::LoadNameSets(QComboBox *box)
{
    box->clear();
    for(auto nameSet : characterNameSetList)
        box->addItem(nameSet.name);
}

void CharacterNameList::LoadNameSetWeight(QLineEdit *edit)
{
    edit->setText(QString::number(characterNameSetList[selectedNameSet].weight));
}

void CharacterNameList::LoadNames(int setIndex, int catIndex, QListView *listView)
{
    if(setIndex>=0 && catIndex>=0)
    {
        selectedNameSet = setIndex;
        characterList->setStringList(characterNameSetList[setIndex].nameList[catIndex]);
        Update(listView);
    }
}

void CharacterNameList::AddNameSet(QString name, TreeItem* treeCharacterName)
{
    TreeItem* newSet = treeCharacterName->InsertKey(name);
    newSet->InsertKey("weight");
    (*newSet)["weight"].InsertKey("100");

    NameListDefaults nld;
    CharacterNameSet set;
    QStringList list;
    set.name = name;
    for(auto cat:nld.character_set_categories)
    {
        set.nameSetCategories.push_back(cat);
        set.nameList.push_back(list);
        newSet->InsertKey(cat);
    }
    characterNameSetList.push_back(set);
}

void CharacterNameList::AddNameCategory(QString category, int setIndex, TreeItem *treeCharacterName)
{
    characterNameSetList[setIndex].nameSetCategories.push_back(category);
    characterNameSetList[setIndex].nameList.push_back(QStringList());
    treeCharacterName[setIndex].InsertKey(category);
}

void CharacterNameList::EditNameList(int setIndex, int catIndex, std::vector<QString> *names, TreeItem *treeCharacterName)
{
    QString cat = characterNameSetList[setIndex].nameSetCategories[catIndex];
    for(auto name:*names)
    {
        characterNameSetList[setIndex].nameList[catIndex].push_back(name);
        (*treeCharacterName)[setIndex][cat].InsertKey(name);
    }
}

void CharacterNameList::EditName(int setIndex, int catIndex, int nameIndex, QString name, TreeItem *treeCharacterName)
{
    QString cat = characterNameSetList[setIndex].nameSetCategories[catIndex];
    (*treeCharacterName)[setIndex][cat][nameIndex].key = name;
    characterNameSetList[setIndex].nameList[catIndex][nameIndex] = name;
}

void CharacterNameList::EditNameSetWeight(int setIndex, int weight)
{
    characterNameSetList[setIndex].weight = weight;
}

CharacterNameSet CharacterNameList::GenerateCharacterNameSet(TreeItem *treeNameSet)
{
    CharacterNameSet set;
    set.weight = (*treeNameSet)["weight"].children[0]->key.replace("\"","").toInt();
    set.name = treeNameSet->key;
    for(int idx = 0;idx<treeNameSet->children.size();idx++)
    {
        auto cat = treeNameSet->children[idx];
        if(cat->key=="weight") continue;
        QStringList list;
        set.nameSetCategories.push_back(cat->key);
        for(auto character:cat->children)
            list.append(character->key);
        set.nameList.push_back(list);
    }
    return set;
}
