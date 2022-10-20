#include "localkeylist.h"

LocalKeyList::LocalKeyList(QWidget *parent)
    : QMainWindow{parent}
{
    keyList = new QStringListModel(this);
}

void LocalKeyList::Update(QListView *listView)
{
    listView->setModel(keyList);
}

void LocalKeyList::LoadKeys(LoadDict* dict)
{
    QStringList list;
    for(auto k:dict->keyPair)
        list.append(k.second);
    keyList->setStringList(list);
}
