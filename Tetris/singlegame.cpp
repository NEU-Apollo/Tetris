#include "singlegame.h"
#include "ui_singlegame.h"
#include "widget.h"
#include <QPainter>
#include <QRect>
#include <QLabel>
#include <QTimer>
#include <QDebug>
#include <QTime>
#include <QRandomGenerator>
#include <QFile>
#include "singlegamegiledialog.h"

SingleGame::SingleGame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SingleGame)
{

    if(over_flag==0)
    {
    ui->setupUi(this);
    setFixedSize(600,700);
    QLabel *numv[20];
    for(int i=0;i<20;i++)
    {
        numv[i]=new QLabel(this);
        numv[i]->move(10,30*i+30);
        numv[i]->setText(QString::number(i));
    }
    QLabel *numh[10];
    for(int i=0;i<10;i++)
    {
        numh[i]=new QLabel(this);
        numh[i]->move(30*i+30,10);
        numh[i]->setText(QString::number(i));
    }
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<20;j++)
        {
            main_matrix[i][j]=0;
        }
    }
    ///////////////////////测试数据/////////////////////////
    now_shape=get_random_number();
    next_shape=get_random_number();
    create_shape(now_shape);
    update();
//    for(int i=0;i<9;i++)
//    {
//        main_matrix[i][19]=2;
//    }
    //////////////////////////////////////////////////////
//    QTimer *down_timer=new QTimer(this);
//    down_timer->start(500);
//    connect(down_timer,&QTimer::timeout,this,[=](){
//        for(int j=18;j>=0;j--)
//        {
//            for(int i=0;i<10;i++)
//            {
//                if(main_matrix[i][j]==1)
//                {
//                    if(main_matrix[i][j+1]==0)
//                    {
//                        main_matrix[i][j]=0;
//                        main_matrix[i][j+1]=1;
//                    }
//                }
//            }
//        }
//        now_shape_pos1Y++;
//        now_shape_pos2Y++;
//        update();
//    });
    //Widget *widegt=new Widget;
    QTimer *crash_timer=new QTimer(this);
    crash_timer->start(500);
    static int crash_flag=0;//碰撞标志
    connect(crash_timer,&QTimer::timeout,this,[=](){
        int down_flag=1;
        for(int j=19;j>=0;j--)
        {
            for(int i=0;i<10;i++)
            {
                if(main_matrix[i][j]==1)
                {
                    if(j==19||main_matrix[i][j+1]==2)
                    {
                        down_flag=0;
                    }
                }
            }
        }
        if(down_flag==1)
        {
            for(int j=18;j>=0;j--)
            {
                for(int i=0;i<10;i++)
                {
                    if(main_matrix[i][j]==1)
                    {
                        main_matrix[i][j]=0;
                        main_matrix[i][j+1]=1;
                    }
                }
            }
            now_shape_pos1Y++;
            now_shape_pos2Y++;
            update();
        }
        //碰撞检测
        else
        {
        for(int i=0;i<10&&crash_flag==0;i++)
        {
            for(int j=19;j>=0&&crash_flag==0;j--)
            {
                if(main_matrix[i][19]==1||(main_matrix[i][j]==2&&main_matrix[i][j-1]==1))
                {
                    crash_flag=1;
                    qDebug()<<"检测到碰撞，crash_flag=1"<<" "<<j-1<<"行";
                    break;
                }
            }
        }
        //检测到碰撞，则进行变运动块为固定块，消除检测，生成下一个的检测，和失败检测
        if(crash_flag==1)
        {
            //变运动块为固定块
            for(int i=0;i<10;i++)
            {
                for(int j=19;j>=0;j--)
                {
                    if(main_matrix[i][j]==1)
                    {
                        main_matrix[i][j]=2;
                    }
                }
            }
            crash_flag=0;
            //消除检测
            for(int j=19;j>=0;)
            {
                int line_sum=0;
                for(int i=0;i<10;i++)
                {
                    line_sum+=main_matrix[i][j];
                }
                if(line_sum==20)
                {
                    addScore(1,now_shape);
                    qDebug()<<j<<"行消除";
                    for(int k=j;k>0;k--)
                    {
                        for(int i=0;i<10;i++)
                        {
                            main_matrix[i][k]=main_matrix[i][k-1];
                        }
                    }
                }
                else
                    j--;
            }
            //失败检测
            for(int i=0;i<10;i++)
            {
                if(main_matrix[i][0]==2)
                {
                    //游戏结束
                    qDebug()<<"游戏结束";
                    addScoreinFile();
                    over_flag=1;
                    crash_timer->stop();
                    this->close();
                    break;
                    //widegt->show();
                }
            }
            //生成下一个块
            if(now_shape==8)
            {
                next_shape=get_random_number();
            }
            //if(over_flag==0)
            //{
            if(over_flag!=1)
            {
                now_shape=next_shape;
                next_shape=get_random_number();
                create_shape(now_shape);
            }
            //}
        }
        update();
        }
    });
//    if(over_flag==1)
//        widegt->show();
    ui->pushButton->setText("暂停");
    connect(ui->pushButton,&QPushButton::clicked,[=](){
        if(ui->pushButton->text()=="暂停")
        {
            crash_timer->stop();
            ui->pushButton->setText("继续");
        }
        else
        {
            crash_timer->start(500);
            ui->pushButton->setText("暂停");
        }
    });
    }
}

void SingleGame::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(QPen(Qt::blue,1));//设置画笔形式
    painter.drawRect(30,30,300,600);//画矩形
    painter.setPen(QPen(Qt::black,1));//设置画笔形式
    for(int i=0;i<19;i++)
    {
       painter.drawLine(30,60+i*30,330,60+i*30);
    }
    for(int i=0;i<9;i++)
    {
       painter.drawLine(60+i*30,30,60+i*30,630);
    }
    for(int i=0;i<5;i++)
    {
       painter.drawLine(430,100+i*30,550,100+i*30);
    }
    for(int i=0;i<5;i++)
    {
       painter.drawLine(430+i*30,100,430+i*30,220);
    }
    painter.translate(30,30);
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<20;j++)
        {
            if(main_matrix[i][j]==1)
            {
                painter.setBrush(Qt::cyan);
                painter.drawRect(30*i,30*j,30,30);
            }
            if(main_matrix[i][j]==2)
            {
                painter.setBrush(Qt::red);
                painter.drawRect(30*i,30*j,30,30);
            }
        }
    }
    painter.translate(400,70);
    painter.setBrush(Qt::cyan);
    switch(next_shape)
    {
    case 0://一
        painter.drawRect(0,30,30,30);
        painter.drawRect(30,30,30,30);
        painter.drawRect(60,30,30,30);
        painter.drawRect(90,30,30,30);
        break;
    case 1://左L
        painter.drawRect(0,30,30,30);
        painter.drawRect(30,30,30,30);
        painter.drawRect(60,30,30,30);
        painter.drawRect(60,60,30,30);
        break;
    case 2://右L
        painter.drawRect(0,30,30,30);
        painter.drawRect(30,30,30,30);
        painter.drawRect(60,30,30,30);
        painter.drawRect(0,60,30,30);
        break;
    case 3://田
        painter.drawRect(30,30,30,30);
        painter.drawRect(30,60,30,30);
        painter.drawRect(60,30,30,30);
        painter.drawRect(60,60,30,30);
        break;
    case 4://Z
        painter.drawRect(0,30,30,30);
        painter.drawRect(30,30,30,30);
        painter.drawRect(30,60,30,30);
        painter.drawRect(60,60,30,30);
        break;
    case 5://反Z
        painter.drawRect(0,60,30,30);
        painter.drawRect(30,60,30,30);
        painter.drawRect(30,30,30,30);
        painter.drawRect(60,30,30,30);
        break;
    case 6://土
        painter.drawRect(0,60,30,30);
        painter.drawRect(30,60,30,30);
        painter.drawRect(60,60,30,30);
        painter.drawRect(30,30,30,30);
        break;

    }
}

void SingleGame::keyPressEvent(QKeyEvent *e)
{
    switch(e->key())
    {
        case Qt::Key_Up:
            switch (now_shape)
            {
                case 0:
                    if(now_shape_num==0&& now_shape_pos1Y>=1 &&main_matrix[now_shape_pos1X+1][now_shape_pos1Y-1]!=2&& now_shape_pos2Y<=17 &&main_matrix[now_shape_pos2X-2][now_shape_pos2Y+2]!=2)
                    {
                        for(int i=now_shape_pos1X;i<=now_shape_pos2X;i++)
                        {
                            main_matrix[i][now_shape_pos1Y]=0;
                        }
                        now_shape_pos1X=now_shape_pos1X+1;
                        now_shape_pos1Y=now_shape_pos1Y-1;
                        now_shape_pos2X=now_shape_pos2X-2;
                        now_shape_pos2Y=now_shape_pos2Y+2;
                        for(int j=now_shape_pos1Y;j<=now_shape_pos2Y;j++)
                        {
                            main_matrix[now_shape_pos1X][j]=1;
                        }
                        now_shape_num=1;
                    }
                    else if(now_shape_num==1&&now_shape_pos1X>0&&now_shape_pos1X<=7&&main_matrix[now_shape_pos1X-1][now_shape_pos1Y+1]!=2&&main_matrix[now_shape_pos1X+1][now_shape_pos1Y+1]!=2&&main_matrix[now_shape_pos1X+2][now_shape_pos1Y+1]!=2)
                    {
                        for(int j=now_shape_pos1Y;j<=now_shape_pos2Y;j++)
                        {
                            main_matrix[now_shape_pos1X][j]=0;
                        }
                        now_shape_pos1X=now_shape_pos1X-1;
                        now_shape_pos1Y=now_shape_pos1Y+1;
                        now_shape_pos2X=now_shape_pos2X+2;
                        now_shape_pos2Y=now_shape_pos2Y-2;
                        for(int i=now_shape_pos1X;i<=now_shape_pos2X;i++)
                        {
                            main_matrix[i][now_shape_pos1Y]=1;
                        }
                        now_shape_num=0;
                    }
                break;
                case 1:
                {
                    if(now_shape_num==0&&now_shape_pos1Y<=17&&main_matrix[now_shape_pos1X][now_shape_pos1Y+1]!=2&&main_matrix[now_shape_pos1X][now_shape_pos1Y+2]!=2)
                    {
                        for(int i=now_shape_pos1X;i<=now_shape_pos2X;i++)
                        {
                            main_matrix[i][now_shape_pos1Y]=0;
                        }
                        main_matrix[now_shape_pos2X][now_shape_pos2Y]=0;
                        now_shape_pos2X=now_shape_pos2X-1;
                        now_shape_pos2Y=now_shape_pos2Y+1;
                        for(int j=now_shape_pos1Y;j<=now_shape_pos2Y;j++)
                        {
                            main_matrix[now_shape_pos1X][j]=1;
                        }
                        main_matrix[now_shape_pos1X+1][now_shape_pos1Y]=1;
                        now_shape_num=1;
                    }
                    else if(now_shape_num==1&&now_shape_pos2Y<=18&&main_matrix[now_shape_pos1X+1][now_shape_pos1Y+1]!=2&&main_matrix[now_shape_pos1X+2][now_shape_pos1Y+1]!=2)
                    {
                        for(int j=now_shape_pos1Y;j<=now_shape_pos2Y;j++)
                        {
                            main_matrix[now_shape_pos1X][j]=0;
                        }
                        main_matrix[now_shape_pos1X+1][now_shape_pos1Y]=0;
                        now_shape_pos2X=now_shape_pos2X+1;
                        now_shape_pos2Y=now_shape_pos2Y-1;
                        for(int i=now_shape_pos1X;i<=now_shape_pos2X;i++)
                        {
                            main_matrix[i][now_shape_pos1Y+1]=1;
                        }
                        main_matrix[now_shape_pos1X][now_shape_pos1Y]=1;
                        now_shape_num=2;
                    }
                    else if(now_shape_num==2
                            &&now_shape_pos2Y<=18
                            &&main_matrix[now_shape_pos1X+2][now_shape_pos1Y]!=2
                            &&main_matrix[now_shape_pos2X][now_shape_pos1Y+1]!=2
                            &&main_matrix[now_shape_pos2X-1][now_shape_pos1Y+1]!=2)
                    {
                        for(int i=now_shape_pos1X;i<=now_shape_pos2X;i++)
                        {
                            main_matrix[i][now_shape_pos1Y+1]=0;
                        }
                        main_matrix[now_shape_pos1X][now_shape_pos1Y]=0;
                        now_shape_pos1X=now_shape_pos1X+1;
                        now_shape_pos2Y=now_shape_pos2Y+1;
                        for(int j=now_shape_pos1Y;j<=now_shape_pos2Y;j++)
                        {
                            main_matrix[now_shape_pos1X+1][j]=1;
                        }
                        main_matrix[now_shape_pos1X][now_shape_pos1Y+2]=1;
                        now_shape_num=3;
                    }
                    else if(now_shape_num==3
                            &&now_shape_pos1X>=1
                            &&main_matrix[now_shape_pos1X-1][now_shape_pos1Y]!=2
                            &&main_matrix[now_shape_pos2X][now_shape_pos1Y]!=2)
                    {
                        for(int j=now_shape_pos1Y;j<=now_shape_pos2Y;j++)
                        {
                            main_matrix[now_shape_pos1X+1][j]=0;
                        }
                        main_matrix[now_shape_pos1X][now_shape_pos1Y+2]=0;
                        now_shape_pos1X=now_shape_pos1X-1;
                        now_shape_pos2Y=now_shape_pos2Y-1;
                        //qDebug()<<now_shape_pos1X<<now_shape_pos1Y<<now_shape_pos2X<<now_shape_pos2Y;
                        for(int i=now_shape_pos1X;i<=now_shape_pos2X;i++)
                        {
                            main_matrix[i][now_shape_pos1Y]=1;
                        }
                        main_matrix[now_shape_pos2X][now_shape_pos2Y]=1;
                        now_shape_num=0;
                    }
                break;
                }
                case 2:
                    if(now_shape_num==0&&now_shape_pos2Y<=18&&main_matrix[now_shape_pos1X+1][now_shape_pos1Y+1]==0&&main_matrix[now_shape_pos1X+1][now_shape_pos1Y+2]==0)
                    {
                        for(int i=now_shape_pos1X;i<=now_shape_pos2X;i++)
                        {
                            main_matrix[i][now_shape_pos1Y]=0;
                        }
                        main_matrix[now_shape_pos1X][now_shape_pos1Y+1]=0;
                        now_shape_pos2X=now_shape_pos2X-1;
                        now_shape_pos2Y=now_shape_pos2Y+1;
//                        qDebug()<<now_shape_num;
//                        qDebug()<<now_shape_pos1X<<now_shape_pos1Y;
//                        qDebug()<<now_shape_pos2X<<now_shape_pos2Y;
                        for(int j=now_shape_pos2Y;j>=now_shape_pos1Y;j--)
                        {
                            main_matrix[now_shape_pos2X][j]=1;
                        }
                        main_matrix[now_shape_pos1X][now_shape_pos1Y]=1;
                        now_shape_num=1;
                    }
                    else if(now_shape_num==1&&now_shape_pos2X<=8&&main_matrix[now_shape_pos1X][now_shape_pos1Y+1]==0&&main_matrix[now_shape_pos1X+2][now_shape_pos1Y]==0&&main_matrix[now_shape_pos1X+2][now_shape_pos1Y+1]==0)
                    {
                        for(int j=now_shape_pos2Y;j>=now_shape_pos1Y;j--)
                        {
                            main_matrix[now_shape_pos2X][j]=0;
                        }
                        main_matrix[now_shape_pos1X][now_shape_pos1Y]=0;
                        now_shape_pos2X=now_shape_pos2X+1;
                        now_shape_pos2Y=now_shape_pos2Y-1;
//                        qDebug()<<now_shape_num;
//                        qDebug()<<now_shape_pos1X<<now_shape_pos1Y;
//                        qDebug()<<now_shape_pos2X<<now_shape_pos2Y;
                        for(int i=now_shape_pos1X;i<=now_shape_pos2X;i++)
                        {
                            main_matrix[i][now_shape_pos2Y]=1;
                        }
                        main_matrix[now_shape_pos2X][now_shape_pos2Y-1]=1;
                        now_shape_num=2;
                    }
                    else if(now_shape_num==2&&now_shape_pos2Y<=18&&main_matrix[now_shape_pos1X][now_shape_pos1Y]==0&&main_matrix[now_shape_pos1X][now_shape_pos1Y+2]==0&&main_matrix[now_shape_pos2X+1][now_shape_pos2Y+2]==0)
                    {
                        for(int i=now_shape_pos1X;i<=now_shape_pos2X;i++)
                        {
                            main_matrix[i][now_shape_pos2Y]=0;
                        }
                        main_matrix[now_shape_pos2X][now_shape_pos2Y-1]=0;
                        now_shape_pos2X=now_shape_pos2X-1;
                        now_shape_pos2Y=now_shape_pos2Y+1;
//                        qDebug()<<now_shape_num;
//                        qDebug()<<now_shape_pos1X<<now_shape_pos1Y;
//                        qDebug()<<now_shape_pos2X<<now_shape_pos2Y;
                        for(int j=now_shape_pos1Y;j<=now_shape_pos2Y;j++)
                        {
                            main_matrix[now_shape_pos1X][j]=1;
                        }
                        main_matrix[now_shape_pos2X][now_shape_pos2Y]=1;
                        now_shape_num=3;
                    }
                    else if(now_shape_num==3&&now_shape_pos2X<=8&&main_matrix[now_shape_pos1X+1][now_shape_pos1Y]==0&&main_matrix[now_shape_pos1X+2][now_shape_pos1Y]==0)
                    {
                        for(int j=now_shape_pos1Y;j<=now_shape_pos2Y;j++)
                        {
                            main_matrix[now_shape_pos1X][j]=0;
                        }
                        main_matrix[now_shape_pos2X][now_shape_pos2Y]=0;
                        now_shape_pos2X=now_shape_pos2X+1;
                        now_shape_pos2Y=now_shape_pos2Y-1;
//                        qDebug()<<now_shape_num;
//                        qDebug()<<now_shape_pos1X<<now_shape_pos1Y;
//                        qDebug()<<now_shape_pos2X<<now_shape_pos2Y;
                        for(int i=now_shape_pos1X;i<=now_shape_pos2X;i++)
                        {
                            main_matrix[i][now_shape_pos1Y]=1;
                        }
                        main_matrix[now_shape_pos1X][now_shape_pos1Y+1]=1;
                        now_shape_num=0;
                    }
                break;
                case 4:
                    if(now_shape_num==0&&now_shape_pos2Y<=18&&main_matrix[now_shape_pos1X][now_shape_pos1Y+1]==0&&main_matrix[now_shape_pos1X][now_shape_pos1Y+2]==0)
                    {
                        main_matrix[now_shape_pos1X][now_shape_pos1Y]=0;
                        main_matrix[now_shape_pos1X+1][now_shape_pos1Y]=0;
                        main_matrix[now_shape_pos1X+1][now_shape_pos1Y+1]=0;
                        main_matrix[now_shape_pos1X+2][now_shape_pos1Y+1]=0;
                        now_shape_pos2X=now_shape_pos2X-1;
                        now_shape_pos2Y=now_shape_pos2Y+1;
                        main_matrix[now_shape_pos1X+1][now_shape_pos1Y]=1;
                        main_matrix[now_shape_pos1X+1][now_shape_pos1Y+1]=1;
                        main_matrix[now_shape_pos1X][now_shape_pos1Y+1]=1;
                        main_matrix[now_shape_pos1X][now_shape_pos1Y+2]=1;
                        now_shape_num=1;
                        //qDebug()<<now_shape_num<<now_shape_pos1X<<now_shape_pos1Y<<now_shape_pos2X<<now_shape_pos2Y;
                    }
                    else if(now_shape_num==1&&now_shape_pos2X<=8&&main_matrix[now_shape_pos1X][now_shape_pos1Y]==0&&main_matrix[now_shape_pos1X+2][now_shape_pos1Y+1]==0)
                    {
                        main_matrix[now_shape_pos1X+1][now_shape_pos1Y]=0;
                        main_matrix[now_shape_pos1X+1][now_shape_pos1Y+1]=0;
                        main_matrix[now_shape_pos1X][now_shape_pos1Y+1]=0;
                        main_matrix[now_shape_pos1X][now_shape_pos1Y+2]=0;
                        now_shape_pos2X=now_shape_pos2X+1;
                        now_shape_pos2Y=now_shape_pos2Y-1;
                        main_matrix[now_shape_pos1X][now_shape_pos1Y]=1;
                        main_matrix[now_shape_pos1X+1][now_shape_pos1Y]=1;
                        main_matrix[now_shape_pos1X+1][now_shape_pos1Y+1]=1;
                        main_matrix[now_shape_pos1X+2][now_shape_pos1Y+1]=1;
                        now_shape_num=0;
                    }
                break;
                case 5:
                    if(now_shape_num==0&&now_shape_pos2Y<=18&&main_matrix[now_shape_pos2X][now_shape_pos2Y]==0&&main_matrix[now_shape_pos2X][now_shape_pos2Y+1]==0)
                    {
                        main_matrix[now_shape_pos1X+1][now_shape_pos1Y]=0;
                        main_matrix[now_shape_pos1X+2][now_shape_pos1Y]=0;
                        main_matrix[now_shape_pos1X][now_shape_pos1Y+1]=0;
                        main_matrix[now_shape_pos1X+1][now_shape_pos1Y+1]=0;
                        now_shape_pos1X=now_shape_pos1X+1;
                        now_shape_pos2Y=now_shape_pos2Y+1;
                        main_matrix[now_shape_pos1X][now_shape_pos1Y]=1;
                        main_matrix[now_shape_pos1X][now_shape_pos1Y+1]=1;
                        main_matrix[now_shape_pos1X+1][now_shape_pos1Y+1]=1;
                        main_matrix[now_shape_pos1X+1][now_shape_pos1Y+2]=1;
                        now_shape_num=1;
                    }
                    else if(now_shape_num==1&&now_shape_pos1X>=1&&main_matrix[now_shape_pos1X+1][now_shape_pos1Y]==0&&main_matrix[now_shape_pos1X-1][now_shape_pos1Y+1]==0)
                    {
                        main_matrix[now_shape_pos1X][now_shape_pos1Y]=0;
                        main_matrix[now_shape_pos1X][now_shape_pos1Y+1]=0;
                        main_matrix[now_shape_pos1X+1][now_shape_pos1Y+1]=0;
                        main_matrix[now_shape_pos1X+1][now_shape_pos1Y+2]=0;
                        now_shape_pos1X=now_shape_pos1X-1;
                        now_shape_pos2Y=now_shape_pos2Y-1;
                        main_matrix[now_shape_pos1X+1][now_shape_pos1Y]=1;
                        main_matrix[now_shape_pos1X+2][now_shape_pos1Y]=1;
                        main_matrix[now_shape_pos1X][now_shape_pos1Y+1]=1;
                        main_matrix[now_shape_pos1X+1][now_shape_pos1Y+1]=1;
                        now_shape_num=0;
                    }
                break;
                case 6:
                if(now_shape_num==0&&now_shape_pos2Y<=18&&main_matrix[now_shape_pos2X-1][now_shape_pos2Y+1]==0)
                {
                    for(int i=now_shape_pos1X;i<=now_shape_pos2X;i++)
                    {
                        main_matrix[i][now_shape_pos2Y]=0;
                    }
                    main_matrix[now_shape_pos1X+1][now_shape_pos1Y]=0;
                    now_shape_pos2X=now_shape_pos2X-1;
                    now_shape_pos2Y=now_shape_pos2Y+1;
                    for(int j=now_shape_pos1Y;j<=now_shape_pos2Y;j++)
                    {
                        main_matrix[now_shape_pos1X+1][j]=1;
                    }
                    main_matrix[now_shape_pos1X][now_shape_pos1Y+1]=1;
                    now_shape_num=1;
                }
                else if(now_shape_num==1&&now_shape_pos2X<=8&&main_matrix[now_shape_pos2X+1][now_shape_pos2Y-1]==0)
                {
                    for(int j=now_shape_pos1Y;j<=now_shape_pos2Y;j++)
                    {
                        main_matrix[now_shape_pos1X+1][j]=0;
                    }
                    main_matrix[now_shape_pos1X][now_shape_pos1Y+1]=0;
                    now_shape_pos1Y=now_shape_pos1Y+1;
                    now_shape_pos2X=now_shape_pos2X+1;
                    for(int i=now_shape_pos1X;i<=now_shape_pos2X;i++)
                    {
                        main_matrix[i][now_shape_pos1Y]=1;
                    }
                    main_matrix[now_shape_pos2X-1][now_shape_pos2Y]=1;
                    now_shape_num=2;
                }
                else if(now_shape_num==2&&now_shape_pos1Y>=1&&main_matrix[now_shape_pos1X+1][now_shape_pos1Y-1]==0)
                {
                    for(int i=now_shape_pos1X;i<=now_shape_pos2X;i++)
                    {
                        main_matrix[i][now_shape_pos1Y]=0;
                    }
                    main_matrix[now_shape_pos2X-1][now_shape_pos2Y]=0;
                    now_shape_pos1X=now_shape_pos1X+1;
                    now_shape_pos1Y=now_shape_pos1Y-1;
                    for(int j=now_shape_pos1Y;j<=now_shape_pos2Y;j++)
                    {
                        main_matrix[now_shape_pos1X][j]=1;
                    }
                    main_matrix[now_shape_pos2X][now_shape_pos2Y-1]=1;
                    now_shape_num=3;
                }
                else if(now_shape_num==3&&now_shape_pos1X>=1&&main_matrix[now_shape_pos1X-1][now_shape_pos1Y+1]==0)
                {
                    for(int j=now_shape_pos1Y;j<=now_shape_pos2Y;j++)
                    {
                        main_matrix[now_shape_pos1X][j]=0;
                    }
                    main_matrix[now_shape_pos2X][now_shape_pos2Y-1]=0;
                    now_shape_pos1X=now_shape_pos1X-1;
                    now_shape_pos2Y=now_shape_pos2Y-1;
                    for(int i=now_shape_pos1X;i<=now_shape_pos2X;i++)
                    {
                        main_matrix[i][now_shape_pos2Y]=1;
                    }
                    main_matrix[now_shape_pos1X+1][now_shape_pos1Y]=1;
                    now_shape_num=0;
                }
                break;
            }
            update();
        break;
        case Qt::Key_Down:
        {
            int down_flag=1;
            for(int j=19;j>=0;j--)
            {
                for(int i=0;i<10;i++)
                {
                    if(main_matrix[i][j]==1)
                    {
                        if(j==19||main_matrix[i][j+1]==2)
                        {
                            down_flag=0;
                        }
                    }
                }
            }
            if(down_flag==1)
            {
                for(int j=18;j>=0;j--)
                {
                    for(int i=0;i<10;i++)
                    {
                        if(main_matrix[i][j]==1)
                        {
                            main_matrix[i][j]=0;
                            main_matrix[i][j+1]=1;
                        }
                    }
                }
                now_shape_pos1Y++;
                now_shape_pos2Y++;
                update();
            }
        break;
        }
        case Qt::Key_Left:
        {
            int left_crash_flag=0;
            for(int j=0;j<20;j++)
            {
                if(main_matrix[0][j]==1)
                {
                    left_crash_flag=1;
                    break;
                }
            }
            if(left_crash_flag==0)
            {
                for(int j=now_shape_pos1Y;j<=now_shape_pos2Y;j++)
                {
                    if(main_matrix[now_shape_pos1X-1][j]==2)
                    {
                        left_crash_flag=1;
                        break;
                    }
                }
            }
            if(left_crash_flag==0)
            {
                for(int i=1;i<=9;i++)
                {
                    for(int j=0;j<20;j++)
                    {
                        if(main_matrix[i][j]==1)
                        {
                            main_matrix[i][j]=0;
                            main_matrix[i-1][j]=1;
                        }

                    }
                }
                now_shape_pos1X--;
                now_shape_pos2X--;
                update();
            }
            break;
        }
        case Qt::Key_Right:
        {
            int right_crash_flag=0;
            for(int j=0;j<20;j++)
            {
                if(main_matrix[9][j]==1)
                {
                    right_crash_flag=1;
                    break;
                }
            }
            if(right_crash_flag==0)
            {
                for(int j=now_shape_pos1Y;j<=now_shape_pos2Y;j++)
                {
                    if(main_matrix[now_shape_pos2X+1][j]==2)
                    {
                        right_crash_flag=1;
                        break;
                    }
                }
            }
            if(right_crash_flag==0)
            {
                for(int i=8;i>=0;i--)
                {
                    for(int j=0;j<20;j++)
                    {
                        if(main_matrix[i][j]==1)
                        {
                            main_matrix[i][j]=0;
                            main_matrix[i+1][j]=1;
                        }

                    }
                }
                now_shape_pos1X++;
                now_shape_pos2X++;
                update();
            }
            break;
        }

        }
}

int SingleGame::get_random_number()
{
    int temp=QRandomGenerator::global()->bounded(7);		//生成一个0和6之间的整数
    qDebug()<<temp;
    return temp;
}

void SingleGame::create_shape(int now_shape)
{
    switch (now_shape)
    {
        case 0://生成一字形状
            for(int i=3;i<=6;i++)
            {
                main_matrix[i][0]=1;
            }
            now_shape_num=0;
            now_shape_pos1X=3;
            now_shape_pos1Y=0;
            now_shape_pos2X=6;
            now_shape_pos2Y=0;
        break;
        case 1://生成左L
            for(int i=4;i<=6;i++)
            {
                main_matrix[i][0]=1;
            }
            main_matrix[6][1]=1;
            now_shape_num=0;
            now_shape_pos1X=4;
            now_shape_pos1Y=0;
            now_shape_pos2X=6;
            now_shape_pos2Y=1;
        break;
        case 2://生成右边L
            for(int i=4;i<=6;i++)
            {
                main_matrix[i][0]=1;
            }
            main_matrix[4][1]=1;
            now_shape_num=0;
            now_shape_pos1X=4;
            now_shape_pos1Y=0;
            now_shape_pos2X=6;
            now_shape_pos2Y=1;
        break;
        case 3://生成田
            main_matrix[4][0]=1;
            main_matrix[4][1]=1;
            main_matrix[5][0]=1;
            main_matrix[5][1]=1;
            now_shape_num=0;
            now_shape_pos1X=4;
            now_shape_pos1Y=0;
            now_shape_pos2X=5;
            now_shape_pos2Y=1;
        break;
        case 4://生成Z
            main_matrix[4][0]=1;
            main_matrix[5][0]=1;
            main_matrix[5][1]=1;
            main_matrix[6][1]=1;
            now_shape_num=0;
            now_shape_pos1X=4;
            now_shape_pos1Y=0;
            now_shape_pos2X=6;
            now_shape_pos2Y=1;
        break;
        case 5://生成反Z
            main_matrix[5][0]=1;
            main_matrix[6][0]=1;
            main_matrix[5][1]=1;
            main_matrix[4][1]=1;
            now_shape_num=0;
            now_shape_pos1X=4;
            now_shape_pos1Y=0;
            now_shape_pos2X=6;
            now_shape_pos2Y=1;
        break;
        case 6://生成土
            main_matrix[5][0]=1;
            main_matrix[4][1]=1;
            main_matrix[5][1]=1;
            main_matrix[6][1]=1;
            now_shape_num=0;
            now_shape_pos1X=4;
            now_shape_pos1Y=0;
            now_shape_pos2X=6;
            now_shape_pos2Y=1;
    }
}

void SingleGame::addScore(int n,int now_shape)
{
    if(now_shape!=8)
    {
        score=score+10*n;
        ui->lcdNumber->display(score);
    }
}

int copy_score;
void SingleGame::addScoreinFile()
{
    //定义文件内容字符串
    copy_score=score;
    SingleGameGileDialog *p=new SingleGameGileDialog;
    p->show();
}

SingleGame::~SingleGame()
{
    delete ui;
}
