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
#include <name_list_defaults.h>

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
    void Clear(QListView* listView, QComboBox *box, QComboBox* box2, QLineEdit* edit);
    void LoadNameList(TreeItem* treeCharacterName);
    void LoadNameCategories(QComboBox* box);
    void LoadNameSets(QComboBox* box);
    void LoadNameSetWeight(QLineEdit* edit);
    void LoadNames(int setIndex, int catIndex, QListView* listView);
    void AddNameSet(QString name, TreeItem* treeCharacterName);
    void AddNameCategory(QString category, int setIndex, TreeItem *treeCharacterName);
    void EditNameList(int setIndex, int catIndex, std::vector<QString>* names, TreeItem *treeCharacterName);
    void EditName(int setIndex, int catIndex, int nameIndex, QString name, TreeItem *treeCharacterName);
    void EditNameSet(QString name, int setIndex, TreeItem *treeCharacterName);
    void EditNameCategory(QString name, int setIndex, int catIndex, TreeItem *treeCharacterName);
    void EditNameSetWeight(int setIndex, int weight);
    void RemoveNameSet(int setIndex, TreeItem *treeCharacterName);
    void RemoveNameCategory(int setIndex, int catIndex, TreeItem *treeCharacterName);

private:
    CharacterNameSet GenerateCharacterNameSet(TreeItem* treeNameSet);

private:
    QStringListModel* characterList;
    std::vector<CharacterNameSet> characterNameSetList;
    int selectedNameSet = 0;
    TreeItem *treeCharacterName;
    QListView* listView_names;
    QComboBox* comboBox_categories;
    QComboBox* comboBox_set;
    QLineEdit* lineEdit_weight;

signals:

};

#endif // CHARACTERNAMELIST_H
