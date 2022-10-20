#ifndef ARMYNAMELIST_H
#define ARMYNAMELIST_H

#include "loaddatafiles.h"
#include <QComboBox>
#include <QListView>
#include <QStringListModel>
#include <QMainWindow>
#include <QTableView>
#include <QAbstractTableModel>

#include <vector>

#include <QDebug>

// Considers that each army category has only a sequential name and no random names
class ArmyModel : public QAbstractTableModel {
   QList<QString> category, name;
public:
   ArmyModel(QObject * parent = {}) : QAbstractTableModel{parent} {}
   int rowCount(const QModelIndex &) const override { return category.count(); }
   int columnCount(const QModelIndex &) const override { return 2; }
   QVariant data(const QModelIndex &index, int role) const override
   {
       if (!index.isValid() || role != Qt::DisplayRole) {
               return QVariant();
       }
       if (index.column() == 0) {
           return category[index.row()];
       } else if (index.column() == 1) {
           return name[index.row()];
       }
       return QVariant();
   }
   QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
      if (orientation != Qt::Horizontal || role != Qt::DisplayRole) return {};
      switch (section) {
      case 0: return "Category";
      case 1: return "Name";
      default: return {};
      }
   }
   void populateData(const QList<QString> &categoryList,const QList<QString> &nameList)
   {
       category.clear();
       category = categoryList;
       name.clear();
       name = nameList;
   }
};

class ArmyNameSet
{
public:
    QString armyCategoryName;
    std::vector<QStringList> nameList;
    std::vector<QString> nameTypeCategories;

    QStringList* operator[](const QString category)
    {
        for(int idx = 0; idx<nameTypeCategories.size() ; idx++)
            if(category == nameTypeCategories[idx])
                return &nameList[idx];
        return nullptr;
    }
};

class ArmyNameList : public QMainWindow
{
    Q_OBJECT
public:
    explicit ArmyNameList(QWidget *parent = nullptr);
    void Update(QListView* listView);
    void LoadNameList(TreeItem* treeArmyName);
    void LoadCategories(QComboBox* box);
    void LoadCategoryNames(QComboBox* box);
    void LoadNames(int catIndex, int typeIndex, QListView* listView);

private:
    ArmyNameSet GenerateArmyNameSet(TreeItem* treeNameSet);

signals:

private:
    int selectedCategory = 0;
    ArmyModel* armyListModel;
    QStringListModel* armyList;
    std::vector<ArmyNameSet> armyNameSetList;
    std::vector<QString> categories = {"machine_defense", "machine_assault_1", "machine_assault_2", "machine_assault_3", "defense_army",
                                       "assault_army", "slave_army", "clone_army", "undead_army", "robotic_army", "robotic_defense_army",
                                       "psionic_army", "xenomorph_army", "gene_warrior_army", "occupation_army", "robotic_occupation_army",
                                       "primitive_army", "industrial_army", "postatomic_army"};

};

#endif // ARMYNAMELIST_H
