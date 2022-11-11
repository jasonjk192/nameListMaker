#include "inputnamesdialog.h"
#include "ui_inputnamesdialog.h"

InputNamesDialog::InputNamesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputNamesDialog)
{
    ui->setupUi(this);
}

InputNamesDialog::~InputNamesDialog()
{
    delete ui;
}

void InputNamesDialog::on_buttonBox_accepted()
{
    QString names = ui->textEdit_nameInput->toPlainText();
    QString delimiter = "\n";
    for(int idx = 0; idx>=0 && idx<names.length(); idx = names.indexOf(delimiter,idx+1))
    {
        QString token = names.mid(idx,names.indexOf(delimiter,idx+1)-idx).remove("\n");
        if(token.size()==0) continue;
        nameList.push_back(token);
    }
}

