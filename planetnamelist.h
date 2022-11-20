#ifndef PLANETNAMELIST_H
#define PLANETNAMELIST_H

#include "loaddatafiles.h"
#include <QMainWindow>
#include <QStringListModel>
#include <QListView>
#include <QComboBox>

#include <QTextStream>
#include <vector>

#include <QDebug>

#include <helperFunctions.h>

class PlanetNameList : public QMainWindow
{
    Q_OBJECT
public:
    explicit PlanetNameList(QWidget *parent = nullptr);
    void Clear(QListView* listView, QComboBox *box);
    void Update(QListView* listView);
    void LoadNameList(TreeItem* treeShipName);
    void LoadCategories(QComboBox* box);
    void LoadNames(int index, QListView* listView);

private:
    QStringListModel* planetList;
    std::vector<QString> categories = {"generic", "pc_desert", "pc_tropical", "pc_arid", "pc_continental", "pc_ocean",
                                       "pc_tundra", "pc_arctic", "pc_savannah", "pc_alpine", "pc_nuked"};
    std::vector<QStringList> planetCategoryBodyList;

signals:

};

#endif // PLANETNAMELIST_H
