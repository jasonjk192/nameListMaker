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
                HelperFunctions::printLine(root->key,"red");
                root->RemoveKey();
            }

        }
        else
        {
            for(int idx=root->children.size()-1;idx>=0;idx--)
                PruneTree(root->children[idx]);
            if(root->children.size()==0)
            {
                HelperFunctions::printLine(root->key,"magenta");
            }
        }
    }

    void SaveKey(TreeItem* root, int depth)
    {
        if(root->children.size()==0)
        {
            if(debugToConsole) HelperFunctions::printLine(HelperFunctions::generateSpace(depth)+root->key,"cyan");
            if(checkIfKeyIsCategory(root->key))
                nameListString.append(HelperFunctions::generateSpace(depth)+root->key+"\r\n");
            else
                nameListString.append(root->key+"\r\n");
        }

        else if(root->children.size()>1)
        {
            if(debugToConsole) HelperFunctions::printLine(HelperFunctions::generateSpace(depth)+root->key + "= {","green");
            nameListString.append(HelperFunctions::generateSpace(depth)+root->key+ " = {\r\n");
        }
        else
        {
            if(root->children[0]->children.size()>0)
            {
                if(debugToConsole) HelperFunctions::printLine(HelperFunctions::generateSpace(depth)+root->key + "= {","blue");
                nameListString.append(HelperFunctions::generateSpace(depth)+root->key+ " = {\r\n");
            }
            else
            {
                if(debugToConsole) HelperFunctions::printLine(HelperFunctions::generateSpace(depth)+root->key + "=","yellow");
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
            if(debugToConsole) HelperFunctions::printLine(HelperFunctions::generateSpace(depth)+"}","green");
            nameListString.append(HelperFunctions::generateSpace(depth)+ "}\r\n");
        }
        else if(root->children.size()==1)
        {
            if(root->children[0]->children.size()>0)
            {
                if(debugToConsole) HelperFunctions::printLine(HelperFunctions::generateSpace(depth)+"}","blue");
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
        QFile file(fileName);
        if (file.open(QIODevice::ReadWrite))
        {
            QTextStream stream(&file);
            stream << sdf.nameListString << endl;
        }
        file.close();
    }

signals:

};

#endif // SAVEDATAFILES_H
