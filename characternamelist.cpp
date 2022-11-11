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

void CharacterNameList::LoadNameList(TreeItem* treeCharacterName)
{
    characterNameSetList.clear();
    if(treeCharacterName->children.size()==0)
    {
        HelperFunctions::printLine("WARNING: character_names do not have any name sets", "yellow");
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

//const std::vector<QString> CharacterNameSet::nameSetCategories = {"first_names", "first_names_male", "first_names_female", "regnal_first_names_male", "regnal_first_names_female",
//        "second_names", "regnal_second_names", "full_names_male", "full_names_female"};


