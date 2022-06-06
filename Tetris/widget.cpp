#include "widget.h"
#include "ui_widget.h"
#include "singlemainmenu.h"
#include "doublemainmeun.h"
#include "exitdialog.h"
#include "setdialog.h"
#include <QPushButton>
#include <QDialog>
#include <QMediaPlayer>
#include <QKeyEvent>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{

    ui->setupUi(this);
    //点击 单人游戏 进入单人游戏界面
    SingleMainMenu *singleMenu=new SingleMainMenu;
    connect(ui->sigleBtn,&QPushButton::clicked,this,[=](){
        this->close();
        singleMenu->show();
    });
    //点击 双人游戏 进入双人游戏界面
    DoubleMainMeun *doubleMenu=new DoubleMainMeun;
    connect(ui->doubleBtn,&QPushButton::clicked,this,[=](){
        this->close();
        doubleMenu->show();
    });
    //点击 退出 弹出对话框
    connect(ui->exitBtn,&QPushButton::clicked,this,[=](){
        ExitDialog *dlg=new ExitDialog;
        int n = dlg->exec();
        if(n == QDialog::Accepted)
        {
           this->close();                //点击确定按钮走这里
        }
        else if( n == QDialog::Rejected)
        {
           dlg->close();               //点击取消按钮走这里
        }
    });
    /*player = new QMediaPlayer(this);
        //connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(postitionChanged(qint64)));
        //player->setMedia(QUrl::fromLocalFile("/F:/qt_project/tetris/music/Faded.mp3"));
        player->setMedia(QUrl::fromLocalFile("F:/qt_project/Tetris/music/Faded.mp3"));
        player->setVolume(200);
        player->play();*/

    //点击 选项 调整游戏难度和音量
//    connect(ui->setBtn,&QPushButton::clicked,this,[=](){
//        SetDialog *dlg=new SetDialog;
//        int n = dlg->exec();
//        if(n == QDialog::Accepted)
//        {
//           dlg->close();                //点击确定按钮走这里
//        }
//    });

}

void Widget::keyPressEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_Down)
    {
        qDebug()<<"down";
    }
}

Widget::~Widget()
{
    delete ui;
}

