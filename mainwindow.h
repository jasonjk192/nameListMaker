#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QMessageBox>
#include <QFileDialog>

#include "shipnamelist.h"
#include "localkeylist.h"
#include "fleetnamelist.h"
#include "armynamelist.h"
#include "planetnamelist.h"
#include "characternamelist.h"

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
    void InitLocalKeyList();
    void InitShipNameList();
    void InitFleetNameList();
    void InitArmyNameList();
    void InitPlanetNameList();
    void InitCharacterNameList();

    // Loads in file data and dump it all into a string
    bool LoadLocalKeyFile(QString* filePath);
    bool LoadNameListFile(QString* filePath);

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
};
#endif // MAINWINDOW_H
