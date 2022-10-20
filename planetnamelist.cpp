#include "planetnamelist.h"

PlanetNameList::PlanetNameList(QWidget *parent)
    : QMainWindow{parent}
{
    planetList = new QStringListModel(this);
}

void PlanetNameList::Update(QListView *listView)
{
    listView->setModel(planetList);
}

void PlanetNameList::LoadNameList(TreeItem* treePlanetName)
{
    if(treePlanetName->children.size()==0)
    {
        HelperFunctions::printLine("WARNING: planet_names do not have any categories", "yellow");
        return;
    }
    categories.clear();
    for(TreeItem* planetType:treePlanetName->children)
    {
        QStringList planetClassList;
        categories.push_back(planetType->key);
        if(planetType[0].children[0]->children.size()==0) HelperFunctions::printLine("WARNING: Planet category \'"+planetType->key+"\' has no names", "yellow");
        for(auto planet:planetType[0].children[0]->children)
            planetClassList.push_back(planet->key);
        planetCategoryBodyList.push_back(planetClassList);
    }
}

void PlanetNameList::LoadCategories(QComboBox *box)
{
    for(auto cat : categories)
        box->addItem(cat);
}

void PlanetNameList::LoadNames(int index, QListView *listView)
{
    planetList->setStringList(planetCategoryBodyList[index]);
    Update(listView);
}
