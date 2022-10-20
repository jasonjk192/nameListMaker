#ifndef CHARACTERNAMELIST_H
#define CHARACTERNAMELIST_H

#include "loaddatafiles.h"
#include <QMainWindow>
#include <QStringListModel>
#include <QListView>
#include <QFile>
#include <QComboBox>
#include <QLineEdit>

#include <QTextStream>
#include <vector>
#include <helperFunctions.h>

#include <QDebug>

class CharacterNameSet
{
public:
    QString name = "default";
    int weight = 100;
    std::vector<QStringList> nameList;
    std::vector<QString> nameSetCategories;

    QStringList* operator[](const QString category)
    {
        for(int idx = 0; idx<nameSetCategories.size() ; idx++)
            if(category == nameSetCategories[idx])
                return &nameList[idx];
        return nullptr;
    }
};

class CharacterNameList : public QMainWindow
{
    Q_OBJECT
public:
    explicit CharacterNameList(QWidget *parent = nullptr);
    void Update(QListView* listView);
    void LoadNameList(TreeItem* treeCharacterName);
    void LoadNameCategories(QComboBox* box);
    void LoadNameSets(QComboBox* box);
    void LoadNameSetWeight(QLineEdit* edit);
    void LoadNames(int setIndex, int catIndex, QListView* listView);

private:
    CharacterNameSet GenerateCharacterNameSet(TreeItem* treeNameSet);

private:
    QStringListModel* characterList;
    std::vector<CharacterNameSet> characterNameSetList;
    int selectedNameSet = 0;

signals:

};

#endif // CHARACTERNAMELIST_H
