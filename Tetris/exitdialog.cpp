#include "exitdialog.h"
#include "ui_exitdialog.h"

ExitDialog::ExitDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExitDialog)
{
    ui->setupUi(this);
    setWindowTitle("退出游戏");
    connect(ui->btnOK,&QPushButton::clicked,this,&ExitDialog::slotOk);
    connect(ui->btnCancel,&QPushButton::clicked,this,&ExitDialog::slotCancel);
}
void ExitDialog::slotOk()
{
    accept();    //隐藏对话框，并且dlg.exec()返回QDialog::Accepted
}

void ExitDialog::slotCancel()
{
    reject();    //隐藏对话框，并且dlg.exec()返回QDialog::Rejected
}
ExitDialog::~ExitDialog()
{
    delete ui;
}
