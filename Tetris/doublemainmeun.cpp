#include "doublemainmeun.h"
#include "ui_doublemainmeun.h"
#include "widget.h"
#include "tetris.h"
#include "ui_tetris.h"

DoubleMainMeun::DoubleMainMeun(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DoubleMainMeun)
{
    setWindowTitle("Tetris");
    setWindowIcon(QIcon("F:\\qt_project\\Tetris\\images\\Tetris.ico"));
    ui->setupUi(this);
    Tetris *t=new Tetris;
    connect(ui->returnBtn,&QPushButton::clicked,this,&DoubleMainMeun::returnmainmenu);
    connect(ui->startBtn,&QPushButton::clicked,this,[=](){
        this->close();
        t->show();
    });
}
void DoubleMainMeun::returnmainmenu()
{
    this->close();//关闭当前界面
    Widget *wdg = new Widget;//创建widget界面
    wdg->show();//显示widget界面
}
DoubleMainMeun::~DoubleMainMeun()
{
    delete ui;
}
