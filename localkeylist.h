#ifndef LOCALKEYLIST_H
#define LOCALKEYLIST_H

#include <QMainWindow>
#include <QStringListModel>
#include <QListView>
#include <QFile>
#include <QTextStream>
#include <loaddatafiles.h>

#include <QDebug>

class LocalKeyList : public QMainWindow
{
    Q_OBJECT
public:
    explicit LocalKeyList(QWidget *parent = nullptr);
    void Update(QListView* listView);
    void LoadKeys(LoadDict* dict);
    void GenerateKeys(LoadDict* dict, TreeItem* root);

private:
    QString ConvertValueToKey(QString* value, LoadDict* dict);
    void CheckKey(TreeItem* root, LoadDict *dict, int depth);
    bool checkIfKeyIsCategory(QString k);
    bool checkIfValueIsSequential(QString* value);

public:
    bool toggleKeys = true;

private:
    QStringListModel* keyList;
    QString keyPrefix;
    bool debugToConsole = false;

signals:

};

#endif // LOCALKEYLIST_H
