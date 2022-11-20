#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->listView_keys->setContextMenuPolicy(Qt::DefaultContextMenu);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//////////////
/// Resets ///
//////////////

void MainWindow::ResetTree()
{
    tree.root.children.clear();
    tree.root.key = "";
}

void MainWindow::ResetDict()
{
    dict.keyPair.clear();
}

void MainWindow::ResetNameList()
{
    localKeyList.Clear(ui->listView_keys);
    shipNameList.Clear(ui->listView_ship, ui->comboBox_ship_categories);
    fleetNameList.Clear(ui->listView_fleet, ui->comboBox_fleet_name_categories);
    armyNameList.Clear(ui->listView_army, ui->comboBox_army_name_categories, ui->comboBox_army_name_type);
    planetNameList.Clear(ui->listView_planet, ui->comboBox_planet_categories);
    characterNameList.Clear(ui->listView_character, ui->comboBox_character_name_categories, ui->comboBox_character_name_set, ui->lineEdit_character_name_set_weight);
}

////////////////////////////////
/// Initialize all the forms ///
////////////////////////////////

void MainWindow::InitShipNameList()
{
    shipNameList.LoadNameList(&tree.root["ship_names"]);
    shipNameList.LoadCategories(ui->comboBox_ship_categories);
    shipNameList.Update(ui->listView_ship);
}

void MainWindow::InitFleetNameList()
{
    fleetNameList.LoadNameList(&tree.root["fleet_names"]);
    fleetNameList.LoadNameCategories(ui->comboBox_fleet_name_categories);
    fleetNameList.Update(ui->listView_fleet);
}

void MainWindow::InitArmyNameList()
{
    armyNameList.LoadNameList(&tree.root["army_names"]);
    armyNameList.LoadCategories(ui->comboBox_army_name_categories);
    armyNameList.Update(ui->listView_army);
}

void MainWindow::InitPlanetNameList()
{
    planetNameList.LoadNameList(&tree.root["planet_names"]);
    planetNameList.LoadCategories(ui->comboBox_planet_categories);
    planetNameList.Update(ui->listView_planet);
}

void MainWindow::InitCharacterNameList()
{
    characterNameList.LoadNameList(&tree.root["character_names"]);
    characterNameList.LoadNameSets(ui->comboBox_character_name_set);
    characterNameList.LoadNameSetWeight(ui->lineEdit_character_name_set_weight);
    characterNameList.Update(ui->listView_character);
}

void MainWindow::UpdateKeys(std::vector<QString> keys, TreeItem *node, QListView *listView)
{
    QStringListModel* model = (QStringListModel*)listView->model();
    QStringList list = model->stringList();
    for(auto key:keys)
    {
        node->InsertKey(key);
        list.append(key);
    }
    model->setStringList(list);
    listView->setModel(model);
}

void MainWindow::InitLocalKeyList()
{
    localKeyList.LoadKeys(&dict);
    localKeyList.Update(ui->listView_keys);
}

//////////////////////////////
/// Load values from files ///
//////////////////////////////

bool MainWindow::LoadLocalKeyFile(QString *filePath)
{
    QFile inputFile(*filePath);
    if (inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile);
        localKeyFileString = in.readAll();
        inputFile.close();
        return true;
    }
    return false;
}

bool MainWindow::LoadNameListFile(QString *filePath)
{
    QFile inputFile(*filePath);
    if (inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile);
        nameListFileString = in.readAll();
        inputFile.close();
        return true;
    }
    return false;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{

    if (event->button()==Qt::RightButton)
    {
        QMenu *menu=new QMenu(this);
        menu->addAction(QString("Add Names"), this,SLOT(on_pushButton_clicked()));
        menu->exec(event->globalPos());
    }
}

////////////////////////////////
/// Signals from Application ///
////////////////////////////////

void MainWindow::on_comboBox_ship_categories_currentIndexChanged(int index)
{
    shipNameList.LoadNames(index, ui->listView_ship);
}

void MainWindow::on_comboBox_fleet_name_categories_currentIndexChanged(int index)
{
    fleetNameList.LoadNames(index, ui->listView_fleet);
}

void MainWindow::on_comboBox_planet_categories_currentIndexChanged(int index)
{
    planetNameList.LoadNames(index, ui->listView_planet);
}

void MainWindow::on_comboBox_character_name_set_currentIndexChanged(int index)
{
    ui->comboBox_character_name_categories->setCurrentIndex(0);
    if(ui->comboBox_character_name_categories->isEnabled() && ui->comboBox_character_name_categories->currentIndex()>=0)
        characterNameList.LoadNames(index>=0?index:0, ui->comboBox_character_name_categories->currentIndex(), ui->listView_character);
    else
        characterNameList.LoadNames(index, 0, ui->listView_character);
    characterNameList.LoadNameCategories(ui->comboBox_character_name_categories);
    characterNameList.LoadNameSetWeight(ui->lineEdit_character_name_set_weight);
}

void MainWindow::on_comboBox_character_name_categories_currentIndexChanged(int index)
{
    if(ui->comboBox_character_name_set->isEnabled() && ui->comboBox_character_name_set->currentIndex()>=0)
        characterNameList.LoadNames(ui->comboBox_character_name_set->currentIndex(), index>=0?index:0, ui->listView_character);
    else
        characterNameList.LoadNames(0, index, ui->listView_character);
}

void MainWindow::on_comboBox_army_name_categories_currentIndexChanged(int index)
{
    ui->comboBox_army_name_type->setCurrentIndex(0);
    if(ui->comboBox_army_name_type->currentIndex()>=0)
        armyNameList.LoadNames(index>=0?index:0, ui->comboBox_army_name_type->currentIndex(), ui->listView_army);
    else
        armyNameList.LoadNames(index, 0, ui->listView_army);
    armyNameList.LoadCategoryNames(ui->comboBox_army_name_type);
}

void MainWindow::on_comboBox_army_name_type_currentIndexChanged(int index)
{
    if(ui->comboBox_army_name_categories->currentIndex()>=0)
        armyNameList.LoadNames(ui->comboBox_army_name_categories->currentIndex(), index>=0?index:0, ui->listView_army);
    else
        armyNameList.LoadNames(0, index, ui->listView_army);
}

void MainWindow::on_actionOpen_Name_List_triggered()
{
    //QString filepath_nameList = stellarisPath+"/common/name_lists/HUMAN1.txt";
    ResetTree();

    QString filter = tr("All files (*.*);;TXT (*.txt)");
    QString filepath_nameList = QFileDialog::getOpenFileName(this, tr("Open File"), tr(""), filter);
    if(filepath_nameList.isEmpty())
        return;
    if(!LoadNameListFile(&filepath_nameList))
    {
        errorMessageBox.setText("Error loading name list at path: "+filepath_nameList);
        errorMessageBox.exec();
    }
    if(!tree.LoadData(&nameListFileString))
    {
        errorMessageBox.setText("Error loading name list data");
        errorMessageBox.exec();
    }
    InitShipNameList();
    InitFleetNameList();
    InitArmyNameList();
    InitPlanetNameList();
    InitCharacterNameList();
}

void MainWindow::on_actionOpen_Localization_triggered()
{
    //QString filepath_localization = stellarisPath+"/localisation/english/name_lists/name_list_HUMAN1_l_english.yml";
    QString filter = tr("All files (*.*);;YML (*.yml)");
    QString filepath_localization = QFileDialog::getOpenFileName(this, tr("Open File"), tr(""), filter);
    if(filepath_localization.isEmpty())
        return;
    if(!LoadLocalKeyFile(&filepath_localization))
    {
        errorMessageBox.setText("Error loading localization at path: "+filepath_localization);
        errorMessageBox.exec();
    }
    if(!dict.LoadData(&localKeyFileString))
    {
        errorMessageBox.setText("Error loading localization data");
        errorMessageBox.exec();
    }
    InitLocalKeyList();
}


void MainWindow::on_pushButton_clicked()
{
    InputNamesDialog dialog;
    if(dialog.exec()==QDialog::Rejected)
        return;
    std::vector<QString> keys;
    for(auto name: dialog.nameList)
        keys.push_back(name);
    TreeItem* currentNode = nullptr;
    QListView* listview;
    int idx = ui->tabWidget_name->currentIndex();
    switch(idx)
    {
        case 1:
                currentNode = &tree.root["ship_names"][ui->comboBox_ship_categories->currentIndex()];
                listview = ui->listView_ship;
                break;
        case 2:
                currentNode = &tree.root["fleet_names"]; listview = ui->listView_fleet;
                break;
        case 3:
                currentNode = &tree.root["army_names"][ui->comboBox_army_name_categories->currentIndex()][ui->comboBox_army_name_type->currentIndex()];
                listview = ui->listView_army;
                break;
        case 4:
                currentNode = &tree.root["planet_names"][ui->comboBox_planet_categories->currentIndex()]["names"];
                listview = ui->listView_planet;
                break;
        case 5:
                currentNode = &tree.root["character_names"][ui->comboBox_character_name_set->currentIndex()][ui->comboBox_character_name_categories->currentIndex()];
                listview = ui->listView_character;
                break;
    default: break;
    }
    if(currentNode!=nullptr)
        UpdateKeys(keys, currentNode, listview);
}


void MainWindow::on_actionName_triggered()
{
    on_pushButton_clicked();
}


void MainWindow::on_actionCreate_New_Name_List_triggered()
{
    NameListDefaults defaults;
    ResetTree();
    tree.root = defaults.GenerateDefaultTree();
    InitShipNameList();
    InitFleetNameList();
    InitArmyNameList();
    InitPlanetNameList();
    InitCharacterNameList();
}


void MainWindow::on_actionSave_As_triggered()
{
    if(!tree.root.children.empty())
        SaveDataFiles::SaveNameList(&tree.root,"");
    else
        HelperFunctions::printLine("No data is available", HelperFunctions::printOption::YELLOW);
    if(dict.keyPair.size()>0)
        SaveDataFiles::SaveLocalization(&dict,"");
    else
        HelperFunctions::printLine("No localization is available/generated", HelperFunctions::printOption::YELLOW);
}


void MainWindow::on_actionLocalization_Keys_triggered()
{
    localKeyList.GenerateKeys(&dict, &tree.root);
    InitLocalKeyList();
    InitShipNameList();
    InitFleetNameList();
    InitArmyNameList();
    InitPlanetNameList();
    InitCharacterNameList();
}


void MainWindow::on_actionToggle_Localization_Keys_triggered(bool checked)
{
    localKeyList.toggleKeys = checked;
    InitLocalKeyList();
}


void MainWindow::on_pushButton_planet_add_category_clicked()
{
    QString category = QInputDialog::getText(this,"New Category","name");
    if(category=="")
        return;
    TreeItem* newcat = tree.root["planet_names"].InsertKey(category);
    newcat->InsertKey("names");
    InitPlanetNameList();
}


void MainWindow::on_actionExit_triggered()
{
    QApplication::exit();
}


void MainWindow::on_actionCloseNameList_triggered()
{
    ResetTree();
    ResetDict();
    ResetNameList();
}


void MainWindow::on_lineEdit_character_name_set_weight_textEdited(const QString &arg1)
{
    bool isNum = true;
    int weight = arg1.toInt(&isNum, 10);
    if(!isNum)
    {
        ui->lineEdit_character_name_set_weight->setText(tree.root["character_names"][ui->comboBox_character_name_set->currentIndex()]["weight"][0].key);
        return;
    }
    tree.root["character_names"][ui->comboBox_character_name_set->currentIndex()]["weight"][0].key = arg1;
    characterNameList.EditNameSetWeight(ui->comboBox_character_name_set->currentIndex(), weight);
}


void MainWindow::on_pushButton_character_add_name_set_clicked()
{
    QString nameSet = QInputDialog::getText(this,"New Name Set","name");
    if(nameSet=="")
        return;
    characterNameList.AddNameSet(nameSet, &tree.root["character_names"]);
    characterNameList.LoadNameSets(ui->comboBox_character_name_set);
}


void MainWindow::on_pushButton_character_add_name_category_clicked()
{
    QString nameCat = QInputDialog::getText(this,"New Name Category","name");
    if(nameCat=="")
        return;
    characterNameList.AddNameCategory(nameCat, ui->comboBox_character_name_set->currentIndex(), &tree.root["character_names"]);
    characterNameList.LoadNameCategories(ui->comboBox_character_name_categories);
}

void MainWindow::on_pushButton_character_add_names_clicked()
{
    InputNamesDialog dialog;
    if(dialog.exec()==QDialog::Rejected)
        return;
    characterNameList.EditNameList(ui->comboBox_character_name_set->currentIndex(), ui->comboBox_character_name_categories->currentIndex(),
                                   &dialog.nameList, &tree.root["character_names"]);
    characterNameList.LoadNames(ui->comboBox_character_name_set->currentIndex(), ui->comboBox_character_name_categories->currentIndex(),
                                ui->listView_character);
}


void MainWindow::on_listView_character_doubleClicked(const QModelIndex &index)
{
    QString newName = QInputDialog::getText(this,"New Name","name");
    if(newName=="")
        return;
    characterNameList.EditName(ui->comboBox_character_name_set->currentIndex(), ui->comboBox_character_name_categories->currentIndex(),
                               index.row(), newName, &tree.root["character_names"]);
    characterNameList.LoadNames(ui->comboBox_character_name_set->currentIndex(), ui->comboBox_character_name_categories->currentIndex(),
                                ui->listView_character);
}

void MainWindow::on_pushButton_army_add_category_clicked()
{
    QString newCat = QInputDialog::getText(this,"New Category","name");
    if(newCat=="")
        return;
    armyNameList.AddCategory(newCat, &tree.root["army_names"]);
    armyNameList.LoadCategories(ui->comboBox_army_name_categories);
}

void MainWindow::on_pushButton_army_add_type_clicked()
{
    QString newType = QInputDialog::getText(this,"New Type","name");
    if(newType=="")
        return;
    armyNameList.AddType(newType, ui->comboBox_army_name_categories->currentIndex(), &tree.root["army_names"]);
    armyNameList.LoadCategoryNames(ui->comboBox_army_name_type);
}

void MainWindow::on_pushButton_army_add_names_clicked()
{
    InputNamesDialog dialog;
    if(dialog.exec()==QDialog::Rejected)
        return;
    armyNameList.EditNameList(ui->comboBox_army_name_categories->currentIndex(), ui->comboBox_army_name_type->currentIndex(),
                              &dialog.nameList, &tree.root["army_names"]);
    armyNameList.LoadNames(ui->comboBox_army_name_categories->currentIndex(), ui->comboBox_army_name_type->currentIndex(),
                           ui->listView_army);
}

void MainWindow::on_listView_army_doubleClicked(const QModelIndex &index)
{
    QString newName = QInputDialog::getText(this,"New Name","name");
    if(newName=="")
        return;
    armyNameList.EditName(ui->comboBox_army_name_categories->currentIndex(), ui->comboBox_army_name_type->currentIndex(),
                               index.row(), newName, &tree.root["army_names"]);
    armyNameList.LoadNames(ui->comboBox_army_name_categories->currentIndex(), ui->comboBox_army_name_type->currentIndex(),
                           ui->listView_army);
}


void MainWindow::on_pushButton_fleet_add_category_clicked()
{
    QString newCat = QInputDialog::getText(this,"New Category","name");
    if(newCat=="")
        return;
    fleetNameList.AddCategory(newCat, &tree.root["fleet_names"]);
    fleetNameList.LoadNameCategories(ui->comboBox_fleet_name_categories);
}


void MainWindow::on_pushButton_fleet_add_names_clicked()
{
    InputNamesDialog dialog;
    if(dialog.exec()==QDialog::Rejected)
        return;
    fleetNameList.EditNameList(ui->comboBox_fleet_name_categories->currentIndex(),
                               &dialog.nameList, &tree.root["fleet_names"]);
    fleetNameList.LoadNames(ui->comboBox_fleet_name_categories->currentIndex(), ui->listView_fleet);
}


void MainWindow::on_listView_fleet_doubleClicked(const QModelIndex &index)
{
    QString newName = QInputDialog::getText(this,"New Name","name");
    if(newName=="")
        return;
    fleetNameList.EditName(ui->comboBox_fleet_name_categories->currentIndex(),
                           index.row(), newName, &tree.root["fleet_names"]);
    fleetNameList.LoadNames(ui->comboBox_fleet_name_categories->currentIndex(), ui->listView_fleet);
}


void MainWindow::on_pushButton_ship_add_category_clicked()
{
    QString newCat = QInputDialog::getText(this,"New Category","name");
    if(newCat=="")
        return;
    shipNameList.AddCategory(newCat, &tree.root["ship_names"]);
    shipNameList.LoadCategories(ui->comboBox_ship_categories);
}


void MainWindow::on_pushButton_ship_add_names_clicked()
{
    InputNamesDialog dialog;
    if(dialog.exec()==QDialog::Rejected)
        return;
    shipNameList.EditNameList(ui->comboBox_ship_categories->currentIndex(),
                              &dialog.nameList, &tree.root["ship_names"]);
    shipNameList.LoadNames(ui->comboBox_ship_categories->currentIndex(), ui->listView_ship);
}


void MainWindow::on_listView_ship_doubleClicked(const QModelIndex &index)
{
    QString newName = QInputDialog::getText(this,"New Name","name");
    if(newName=="")
        return;
    shipNameList.EditName(ui->comboBox_ship_categories->currentIndex(),
                          index.row(), newName, &tree.root["ship_names"]);
    shipNameList.LoadNames(ui->comboBox_ship_categories->currentIndex(), ui->listView_ship);
}
