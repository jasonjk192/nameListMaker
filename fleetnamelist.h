#ifndef FLEETNAMELIST_H
#define FLEETNAMELIST_H

#include <QMainWindow>
#include <QStringListModel>
#include <QListView>
#include <QFile>
#include <QComboBox>

#include <QTextStream>
#include <vector>
#include <helperFunctions.h>
#include "loaddatafiles.h"

#include <QDebug>

class FleetNameList : public QMainWindow
{
    Q_OBJECT
public:
    explicit FleetNameList(QWidget *parent = nullptr);
    void Update(QListView* listView);
    void LoadNameList(TreeItem* treeFleetName);
    void LoadNameCategories(QComboBox* box);
    void LoadNames(int index, QListView* listView);

private:
    QStringListModel* fleetList;

    std::vector<QStringList> fleetNameStringList;

    std::vector<QString> name_categories = {"random_names", "sequential_name"};

signals:

};

#endif // FLEETNAMELIST_H
