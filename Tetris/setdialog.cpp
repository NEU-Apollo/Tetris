#include "setdialog.h"
#include "ui_setdialog.h"
#include <QDebug>

SetDialog::SetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetDialog)
{
    ui->setupUi(this);
    connect(ui->pushButton_2,&QPushButton::clicked,this,&SetDialog::slotOk);
}

void SetDialog::slotOk()
{
    music=ui->horizontalSlider->value();
    qDebug()<<"音量："<<music;
    level=ui->horizontalSlider_2->value();
    qDebug()<<"难度："<<level;
    accept();
}

int SetDialog::getlevel()
{
    return level;
}

int SetDialog::getmusic()
{
    return music;
}

SetDialog::~SetDialog()
{
    delete ui;
}
