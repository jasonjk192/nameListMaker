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

private:
    QStringListModel* keyList;

signals:

};

#endif // LOCALKEYLIST_H
