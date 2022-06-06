#include "singlemainmenu.h"
#include "ui_singlemainmenu.h"
#include "singlegame.h"
#include "widget.h"
#include "singlerank.h"
SingleMainMenu::SingleMainMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SingleMainMenu)
{
    setWindowTitle("Tetris");
    setWindowIcon(QIcon("F:\\qt_project\\Tetris\\images\\Tetris.ico"));
    ui->setupUi(this);
    connect(ui->returnBtn,&QPushButton::clicked,this,&SingleMainMenu::returnmainmenu);
    connect(ui->startBtn,&QPushButton::clicked,this,[=](){
        SingleGame *singlegame=new SingleGame;
        this->close();
        singlegame->show();
    });
    SingleRank *singlerank=new SingleRank;
    connect(ui->rankBtn,&QPushButton::clicked,this,[=](){

        this->close();
        singlerank->show();
    });
}

void SingleMainMenu::returnmainmenu()
{
    this->close();//关闭当前界面
    Widget *wdg = new Widget;//创建widget界面
    wdg->show();//显示widget界面
}

SingleMainMenu::~SingleMainMenu()
{
    delete ui;
}
