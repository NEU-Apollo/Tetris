#include "singlerank.h"
#include "ui_singlerank.h"
#include <string>
#include "widget.h"
using namespace std;

SingleRank::SingleRank(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SingleRank)
{

    typedef struct menu
    {
        string name;
        int score;
        struct menu *next;
    }menu;
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"昵称"<<"分数");
    ui->tableWidget->setRowCount(100);
    FILE *f;
    f=fopen("F:\\qt_project\\Tetris\\singleRank.txt","r");
    menu *p=new menu;
    menu *p1=p;
    int score=0;
    char name[100];
    //int i=0;
    int number=0;
    while(fscanf(f,"%d%s",&score,name)!=EOF)
    {
        p1=p1->next=new menu;
        p1->name=name;
        p1->score=score;
        p1->next=nullptr;
       QString strQ = QString::fromLocal8Bit(p1->name.c_str());
        ui->tableWidget->setItem(number,1,new QTableWidgetItem(QString::number(score)));
        ui->tableWidget->setItem(number,0,new QTableWidgetItem(strQ));
        number++;
    }

    menu *p_sort=new menu;
    p1=p->next;
    p_sort->next=nullptr;
    menu *p1_sort=p_sort->next;
    menu *p2_sort=p_sort;
    for(;number>0;number--)
    {
        if(p1!=nullptr&&p1_sort!=nullptr)
        {
            while(p1_sort->score>p1->score)
            {
                p1_sort=p1_sort->next;
                p2_sort=p2_sort->next;
                if(p1_sort==nullptr)
                {
                    break;
                }
            }
        }
        if(p1!=nullptr)
        {
            p2_sort->next=new menu;
            p2_sort->next->name=p1->name;
            p2_sort->next->score=p1->score;
            p2_sort->next->next=p1_sort;
            p1=p1->next;
            p1_sort=p_sort->next;
            p2_sort=p_sort;
        }
    }
    p1_sort=p_sort->next;

    while(p1_sort!=nullptr)
    {
        QString strQ = QString::fromLocal8Bit(p1_sort->name.c_str());
        ui->tableWidget->setItem(number,1,new QTableWidgetItem(QString::number(p1_sort->score)));
        ui->tableWidget->setItem(number,0,new QTableWidgetItem(strQ));
        number++;
        p1_sort=p1_sort->next;
    }
    fclose(f);

    connect(ui->pushButton,&QPushButton::clicked,this,[=](){
        Widget *widegt=new Widget;
        this->close();
        widegt->show();
    });

}

SingleRank::~SingleRank()
{
    delete ui;
}
