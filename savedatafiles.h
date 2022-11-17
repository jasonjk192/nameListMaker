#ifndef SAVEDATAFILES_H
#define SAVEDATAFILES_H

#include <QMainWindow>
#include "loaddatafiles.h"
#include "helperFunctions.h"
#include "name_list_defaults.h"

#include <QString>

class SaveDataFiles : public QMainWindow
{
    Q_OBJECT

private:
    QString nameListString = "";
    bool debugToConsole = true;
    NameListDefaults def;

    bool checkIfKeyIsCategory(QString k)
    {
        if(k=="names") return true;
        if(k=="weight") return true;
        for(auto cat:def.species_name_categories) if(k==cat) return true;
        for(auto cat:def.army_categories) if(k==cat) return true;
        for(auto cat:def.planet_categories) if(k==cat) return true;
        for(auto cat:def.ship_categories) if(k==cat) return true;
        for(auto cat:def.character_set_categories) if(k==cat) return true;
        for(auto cat:def.random_sequential_categories) if(k==cat) return true;
        return false;
    }

    void PruneTree(TreeItem* root)
    {
        if(root->children.size()==0)
        {
            if(checkIfKeyIsCategory(root->key))
            {
                HelperFunctions::printLine(root->key,HelperFunctions::printOption::RED);
                root->RemoveKey();
            }

        }
        else
        {
            for(int idx=root->children.size()-1;idx>=0;idx--)
                PruneTree(root->children[idx]);
            if(root->children.size()==0)
            {
                HelperFunctions::printLine(root->key,HelperFunctions::printOption::MAGENTA);
            }
        }
    }

    void SaveKey(TreeItem* root, int depth)
    {
        if(root->children.size()==0)
        {

            if(checkIfKeyIsCategory(root->key))
            {
                if(debugToConsole) HelperFunctions::printLine(HelperFunctions::generateSpace(depth)+root->key+" = {}",HelperFunctions::printOption::STRONG_CYAN);
                nameListString.append(HelperFunctions::generateSpace(depth)+root->key+" = {}\r\n");
            }

            else
            {
                if(debugToConsole) HelperFunctions::printLine(HelperFunctions::generateSpace(depth)+root->key,HelperFunctions::printOption::CYAN);
                if(root->parent->children.size()==1)
                    nameListString.append(root->key+"\r\n");
                else
                    nameListString.append(HelperFunctions::generateSpace(depth)+root->key+"\r\n");
            }
        }

        else if(root->children.size()>1)
        {
            if(debugToConsole) HelperFunctions::printLine(HelperFunctions::generateSpace(depth)+root->key + "= {",HelperFunctions::printOption::GREEN);
            nameListString.append(HelperFunctions::generateSpace(depth)+root->key+ " = {\r\n");
        }
        else
        {
            if(root->children[0]->children.size()>0)
            {
                if(debugToConsole) HelperFunctions::printLine(HelperFunctions::generateSpace(depth)+root->key + "= {",HelperFunctions::printOption::BLUE);
                nameListString.append(HelperFunctions::generateSpace(depth)+root->key+ " = {\r\n");
            }
            else
            {
                if(debugToConsole) HelperFunctions::printLine(HelperFunctions::generateSpace(depth)+root->key + "=",HelperFunctions::printOption::YELLOW);
                nameListString.append(HelperFunctions::generateSpace(depth)+root->key+ " = ");
            }
        }

        if(root->children.size()>0)
            for(auto child:root->children)
            {
                SaveKey(child, depth+1);
            }
        if(root->children.size()>1)
        {
            if(debugToConsole) HelperFunctions::printLine(HelperFunctions::generateSpace(depth)+"}",HelperFunctions::printOption::GREEN);
            nameListString.append(HelperFunctions::generateSpace(depth)+ "}\r\n");
        }
        else if(root->children.size()==1)
        {
            if(root->children[0]->children.size()>0)
            {
                if(debugToConsole) HelperFunctions::printLine(HelperFunctions::generateSpace(depth)+"}",HelperFunctions::printOption::BLUE);
                nameListString.append(HelperFunctions::generateSpace(depth)+ "}\r\n");
            }
        }
    }


public:
    explicit SaveDataFiles(QWidget *parent = nullptr); 
    static void SaveNameList(TreeItem* root, QString fileName)
    {
        SaveDataFiles sdf;
        sdf.SaveKey(root,0);
        QFile file("E:/db/test.txt");
        if (file.open(QIODevice::ReadWrite))
        {
            QTextStream stream(&file);
            stream << sdf.nameListString << endl;
        }
        file.close();
    }
    static void SaveLocalization(LoadDict *dict, QString fileName)
    {
        QString localListString = "l_english:\r\n";
        for(auto k:dict->keyPair)
            localListString.append(k.first+":0 "+"\""+k.second+"\"\r\n");
        QFile file("E:/db/local_test.yml");
        if (file.open(QIODevice::ReadWrite))
        {
            QTextStream stream(&file);
            stream << localListString << endl;
        }
        file.close();
    }

signals:

};

#endif // SAVEDATAFILES_H
