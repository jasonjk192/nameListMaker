#ifndef SAVEDATAFILES_H
#define SAVEDATAFILES_H

#include <QMainWindow>
#include <QInputDialog>
#include <QString>

#include "loaddatafiles.h"
#include "helperFunctions.h"
#include "name_list_defaults.h"

class SaveDataFiles : public QMainWindow
{
    Q_OBJECT

private:
    QString nameListString = "";
    bool debugToConsole = false;
    NameListDefaults def;

    void PruneTree(TreeItem* root)
    {
        if(root->children.size()==0)
        {
            if(def.CheckIfKeyIsCategory(root->key))
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
            if(def.CheckIfKeyIsCategory(root->key) || root->children.size()>0)
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
        QFile file("E:/"+fileName+".txt");
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
        QFile file("./"+fileName);
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
