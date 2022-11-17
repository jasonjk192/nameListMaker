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
    if(toggleKeys)
        for(auto k:dict->keyPair)
            list.append(k.first);
    else
        for(auto k:dict->keyPair)
            list.append(k.second);
    keyList->setStringList(list);
}

void LocalKeyList::CheckKey(TreeItem* root, LoadDict *dict, int depth)
{
    if(root->children.size()==0)
    {
        if(debugToConsole) HelperFunctions::printLine(HelperFunctions::generateSpace(depth)+root->key,HelperFunctions::printOption::CYAN);
        auto value = dict->keyPair.find(root->key);
        if(value == dict->keyPair.end())
        {
            HelperFunctions::printLine(root->key,HelperFunctions::printOption::RED);
            root->key = ConvertValueToKey(&root->key, dict);
        }

        else
            HelperFunctions::printLine(value->first,value->second, HelperFunctions::printOption::CYAN);
    }

    else if(root->children.size()>1)
    {
        if(debugToConsole) HelperFunctions::printLine(HelperFunctions::generateSpace(depth)+root->key + "= {",HelperFunctions::printOption::GREEN);
    }
    else
    {
        if(root->children[0]->children.size()>0)
        {
            if(debugToConsole) HelperFunctions::printLine(HelperFunctions::generateSpace(depth)+root->key + "= {",HelperFunctions::printOption::BLUE);

        }
        else
        {
            if(debugToConsole) HelperFunctions::printLine(HelperFunctions::generateSpace(depth)+root->key + "=",HelperFunctions::printOption::YELLOW);

        }
    }

    if(root->children.size()>0)
        for(auto child:root->children)
        {
            CheckKey(child, dict, depth+1);
        }
    if(root->children.size()>1)
    {
        if(debugToConsole) HelperFunctions::printLine(HelperFunctions::generateSpace(depth)+"}",HelperFunctions::printOption::GREEN);

    }
    else if(root->children.size()==1)
    {
        if(root->children[0]->children.size()>0)
        {
            if(debugToConsole) HelperFunctions::printLine(HelperFunctions::generateSpace(depth)+"}",HelperFunctions::printOption::BLUE);

        }
    }
}

void LocalKeyList::GenerateKeys(LoadDict *dict, TreeItem* root)
{
    QString aliasName = (*root)["alias"].children[0]->key;
    keyPrefix = aliasName.replace("\"","");
    keyPrefix = keyPrefix.left(3).toUpper();
    //HelperFunctions::printLine(keyPrefix,HelperFunctions::printOption::BLUE);
    CheckKey(root,dict,0);
    for(auto k:dict->keyPair)
        HelperFunctions::printLine(k.first,k.second,HelperFunctions::printOption::GREEN);
}

QString LocalKeyList::ConvertValueToKey(QString *value, LoadDict *dict)
{
    for(auto k:dict->keyPair)
        if(k.second==*value) return k.first;
    QString word = *value;
    word = word.replace("\"","").replace("\'","").replace(" ","");
    QString key = keyPrefix+"_"+word;
    if(checkIfValueIsSequential(value))
    {
        word = word.replace("$O$","xx").replace("$C$","xx").replace("$R$","xx")
                .replace("%O%","xx").replace("%C%","xx").replace("%R%","xx");
        word.append("_SEQ");
        key = keyPrefix+"_"+word;
    }

    dict->keyPair[key] = (*value).replace("\"","");
    if(debugToConsole) HelperFunctions::printLine(key,HelperFunctions::printOption::YELLOW);
    return key;
}

bool LocalKeyList::checkIfValueIsSequential(QString* value)
{
    if(value->contains("$O$")||value->contains("$C$")||value->contains("$R$")||
            value->contains("%O%")||value->contains("%C%")||value->contains("%R%"))
        return true;
    return false;
}
