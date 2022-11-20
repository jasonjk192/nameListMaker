#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QMessageBox>
#include <QFileDialog>
#include <QFormLayout>
#include <QMouseEvent>
#include <QInputDialog>

#include "shipnamelist.h"
#include "localkeylist.h"
#include "fleetnamelist.h"
#include "armynamelist.h"
#include "planetnamelist.h"
#include "characternamelist.h"
#include "savedatafiles.h"
#include "loaddatafiles.h"
#include "inputnamesdialog.h"
#include "name_list_defaults.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void ResetTree();
    void ResetDict();
    void ResetNameList();

    void InitLocalKeyList();
    void InitShipNameList();
    void InitFleetNameList();
    void InitArmyNameList();
    void InitPlanetNameList();
    void InitCharacterNameList();

    void UpdateKeys(std::vector<QString> keys, TreeItem* node, QListView* listView);

    // Loads in file data and dump it all into a string
    bool LoadLocalKeyFile(QString* filePath);
    bool LoadNameListFile(QString* filePath);

    void mousePressEvent(QMouseEvent *event);

private slots:
    void on_comboBox_ship_categories_currentIndexChanged(int index);

    void on_comboBox_fleet_name_categories_currentIndexChanged(int index);

    void on_comboBox_planet_categories_currentIndexChanged(int index);

    void on_comboBox_character_name_set_currentIndexChanged(int index);

    void on_comboBox_character_name_categories_currentIndexChanged(int index);

    void on_comboBox_army_name_categories_currentIndexChanged(int index);

    void on_comboBox_army_name_type_currentIndexChanged(int index);

    void on_actionOpen_Name_List_triggered();

    void on_actionOpen_Localization_triggered();

    void on_pushButton_clicked();

    void on_actionName_triggered();

    void on_actionCreate_New_Name_List_triggered();

    void on_actionSave_As_triggered();

    void on_actionLocalization_Keys_triggered();

    void on_actionToggle_Localization_Keys_triggered(bool checked);

    void on_pushButton_planet_add_category_clicked();

    void on_actionExit_triggered();

    void on_actionCloseNameList_triggered();

    void on_lineEdit_character_name_set_weight_textEdited(const QString &arg1);

    void on_pushButton_character_add_name_set_clicked();

    void on_pushButton_character_add_name_category_clicked();

    void on_pushButton_character_add_names_clicked();

    void on_listView_character_doubleClicked(const QModelIndex &index);

    void on_pushButton_army_add_category_clicked();

    void on_pushButton_army_add_names_clicked();

    void on_pushButton_army_add_type_clicked();

    void on_listView_army_doubleClicked(const QModelIndex &index);

    void on_pushButton_fleet_add_category_clicked();

    void on_pushButton_fleet_add_names_clicked();

    void on_listView_fleet_doubleClicked(const QModelIndex &index);

    void on_pushButton_ship_add_category_clicked();

    void on_pushButton_ship_add_names_clicked();

    void on_listView_ship_doubleClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    ShipNameList shipNameList;
    FleetNameList fleetNameList;
    ArmyNameList armyNameList;
    PlanetNameList planetNameList;
    CharacterNameList characterNameList;
    LocalKeyList localKeyList;
    QMessageBox errorMessageBox;
    QString localKeyFileString;
    QString nameListFileString;
    LoadTree tree;
    LoadDict dict;
    std::vector<QString> userCategories;
};
#endif // MAINWINDOW_H
