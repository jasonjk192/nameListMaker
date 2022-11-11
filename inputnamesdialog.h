#ifndef INPUTNAMESDIALOG_H
#define INPUTNAMESDIALOG_H

#include <QDialog>
#include "helperFunctions.h"

namespace Ui {
class InputNamesDialog;
}

class InputNamesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InputNamesDialog(QWidget *parent = nullptr);
    ~InputNamesDialog();

    std::vector<QString> nameList;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::InputNamesDialog *ui;
};

#endif // INPUTNAMESDIALOG_H
