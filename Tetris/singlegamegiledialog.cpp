#include "singlegamegiledialog.h"
#include "ui_singlegamegiledialog.h"
#include "singlegame.h"
#include <QFile>
#include <QDebug>
#include "widget.h"
extern int copy_score;
SingleGameGileDialog::SingleGameGileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SingleGameGileDialog)
{
    ui->setupUi(this);
    ui->label_score->setNum(copy_score);
    connect(ui->pushButton,&QPushButton::clicked,this,[=]{
        this->close();
        Widget *wdg = new Widget;//创建widget界面
        wdg->show();//显示widget界面
    });
}

SingleGameGileDialog::~SingleGameGileDialog()
{
    delete ui;
}

void SingleGameGileDialog::on_lineEdit_editingFinished()
{
    QString str= QString::number(copy_score,10);
    static QString strstr;
    strstr=ui->lineEdit->text();
    qDebug()<<strstr;
    str.append(" ");
    str.append(strstr);
    str.append("\n");
    QFile file("F:\\qt_project\\Tetris\\singleRank.txt");
    //打开文件，不存在则创建
    file.open(QIODevice::ReadWrite | QIODevice::Append);
    //写入文件需要字符串为QByteArray格式
    file.write(str.toUtf8());
    file.close();

}

void SingleGameGileDialog::keyPressEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_Enter)
    {
        this->close();
    }
}

