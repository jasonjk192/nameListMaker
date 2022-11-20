#ifndef SHIPNAMELIST_H
#define SHIPNAMELIST_H

#include <QMainWindow>
#include <QStringListModel>
#include <QListView>
#include <QComboBox>

#include <QTextStream>
#include <vector>
#include <helperFunctions.h>
#include "loaddatafiles.h"

#include <QDebug>

class ShipNameList : public QMainWindow
{
    Q_OBJECT
public:
    explicit ShipNameList(QMainWindow *parent = nullptr);
    void Update(QListView* listView);
    void Clear(QListView* listView, QComboBox *box);
    void LoadNameList(TreeItem* treeShipName);
    void LoadCategories(QComboBox* box);
    void LoadNames(int index, QListView* listView);
    void AddCategory(QString name, TreeItem *treeShipName);
    void EditNameList(int index, std::vector<QString> *names, TreeItem *treeShipName);
    void EditName(int index, int nameIndex, QString name, TreeItem *treeShipName);

private:
    QStringListModel* shipList;
    std::vector<QString> categories = {"generic", "corvette", "destroyer", "cruiser", "battleship", "titan", "colossus", "constructor",
                                       "colonizer", "science", "transport", "military_station_small", "ion_cannon"};
    std::vector<QStringList> shipCategoryBodyList;
    QRegularExpression re;
    QRegularExpressionMatch match;

signals:

};

#endif // SHIPNAMELIST_H
