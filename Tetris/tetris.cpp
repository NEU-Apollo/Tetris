#include "tetris.h"
#include "ui_tetris.h"

#include <QDebug>
#include <QMessageBox>
#include <QTimerEvent>
#include <QPainter>
#include <QTime>

#define NUM_BRICK_TYPES 7
#define	NUM_TURNS_PER_STEP 3
#define COLOR_CHANGE 60

Tetris::Tetris(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Tetris)
{
    ui->setupUi(this);
    setFixedSize(848,440);
    init();
    setWindowTitle("DoubleGame");
    setWindowIcon(QIcon("F:\\qt_project\\Tetris\\images\\Tetris.ico"));
     connect(ui->action_start, SIGNAL(triggered()), this, SLOT(gameStart()));
     connect(ui->action_pause, SIGNAL(triggered()), this, SLOT(onPause()));
     connect(ui->action_quit, SIGNAL(triggered()), this, SLOT(close()));
     connect(ui->action_easy, SIGNAL(triggered()), this, SLOT(onDiffEasy()));
     connect(ui->action_middle, SIGNAL(triggered()), this, SLOT(onDiffMid()));
     connect(ui->action_difficult, SIGNAL(triggered()), this, SLOT(onDiffSup()));
    // connect(ui->, SIGNAL(triggered()), this, SLOT(gameStart()));

}

Tetris::~Tetris()
{
    delete ui;

    delete bin;
    delete bin1;
    delete bin2;
    delete bin3;
}
void Tetris::init()
{
    bin=new CBin(10,20);
    bin1=new CBin(10,20);
    bin2=new CBin(10,20);
    bin3=new CBin(10,20);
    activeBrick=NULL;
    activeBrick1=NULL;
    activeBrick2=NULL;
    activeBrick3=NULL;
    gameOver=1;
    gameOver1=1;
    brickInFlight=1;
    brickInFlight1=1;
    brickType=0;
    brickType1=0;
    brickType2=0;
    brickType3=0;
    initOrientation=0;
    initOrientation1=0;
    initOrientation2=0;
    initOrientation3=0;
    notCollide=0;
    notCollide1=0;
    numLines=0;
    numLines1=0;
    difficulty=500;
    RandomFlag=false;
    RandomFlag1=false;
    Pause1=Pause2=false;
    p=false;
    Flag=false;
    modal=false;
    GameModal=2;
    image =new unsigned char*[20];
    image1 =new unsigned char*[20];
    image2 =new unsigned char*[20];
    image3 =new unsigned char*[20];
    for(int i=0;i<20;i++)
    {
        image[i]=new unsigned char[10];
        image1[i]=new unsigned char[10];
        image2[i]=new unsigned char[10];
        image3[i]=new unsigned char[10];
    }
    bin->getImage(image);
    bin1->getImage(image1);
    bin2->getImage(image2);
    bin3->getImage(image3);
    ////////////
}

void Tetris::gameStart()
{
    gameOver=0;
    brickInFlight=0;
    numLines=0;
    //------------
    gameOver1=0;
    brickInFlight1=0;
    numLines1=0;
    for(unsigned int i=0;i<20;i++)
    {
        for(unsigned int j=0;j<10;j++)
        {
            image[i][j]=0;
            image1[i][j]=0;
            image2[i][j]=0;
            image3[i][j]=0;
        }
    }
    bin->setImage(image);
    bin1->setImage(image1);
    bin2->setImage(image2);
    bin3->setImage(image3);

    timerID = startTimer(difficulty);
}

void Tetris::onPause()
{
    if(!p)   //原先没有暂停则暂停
    {
    Pause1=true;  //设置暂停为真
    Pause2=true;
    p=true;
    }
    else   //若原先暂停，按下后继续游戏
    {
    Pause1=false;
    Pause2 =false;
    p = false;
    }
}

void Tetris::onDiffEasy()
{
    difficulty=500;
}

void Tetris::onDiffMid()
{
    difficulty=300;
}

void Tetris::onDiffSup()
{
    difficulty=150;
}


/////////////////////////////////////////////

void Tetris::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space)
        onPause();

    if(event->key() == Qt::Key_Right)
        activeBrick->shiftRight(bin);
    else if(event->key() == Qt::Key_Left)
        activeBrick->shiftLeft(bin);
    else if(event->key() == Qt::Key_Up)
        activeBrick->rotateClockwise(bin);
    else if(event->key() == Qt::Key_Down)
        activeBrick->shiftDown(bin);

    if(event->key() == Qt::Key_D)
        activeBrick2->shiftRight(bin2);
    else if(event->key() == Qt::Key_A)
        activeBrick2->shiftLeft(bin2);
    else if(event->key() == Qt::Key_W)
        activeBrick2->rotateClockwise(bin2);
    else if(event->key() == Qt::Key_S)
        activeBrick2->shiftDown(bin2);

}

void Tetris::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == timerID)
    {
        unsigned int binWidth,binHeight,binWidth1,binHeight1;
        unsigned int binWidth2,binHeight2,binWidth3,binHeight3;

       // CDC *pDC=GetDC();
        binWidth=bin->getWidth();    //获得左边主面板宽度
        binHeight=bin->getHeight();  //获得左边主面板高度
        //----------
        binWidth1=bin1->getWidth();  //获得左边预测面板宽度
        binHeight1=bin1->getHeight();//获得左边预测面板宽度

        binWidth2=bin2->getWidth();   //获得右边主面板宽度
        binHeight2=bin2->getHeight();   //获得右边主面板宽度
        //----------
        binWidth3=bin3->getWidth();   //获得右边预测面板宽度
        binHeight3=bin3->getHeight();  //获得右边预测面板宽度

        if(!brickInFlight&&!gameOver)  //判断左边游戏是否结束及砖块是否在飞
        {

            if(!RandomFlag)  //若是第一次产生主界面砖块类型，则执行下面语句（第一次产生的砖块不是预测的）下面语句只执行一次
            {

              brickType=((unsigned int)qrand()%NUM_BRICK_TYPES)+1;
              initOrientation=(unsigned int)(qrand()%4);
              RandomFlag=true;
            }
            else //第二次以后，主界面的砖块都是上一次预测砖块的类型
            {
                brickType=brickType1;
                initOrientation=initOrientation1;
            }
            qsrand(QTime::currentTime().second());                          //预测砖块类型的产生
            brickType1=(qrand()%NUM_BRICK_TYPES)+1;
            initOrientation1=(unsigned int)(qrand()%4);


            //若为经典模式
            {
               if(brickType==1)
                activeBrick=new CTBrick;
            else if(brickType==2)
                activeBrick=new CABrick;
            else if(brickType==3)
                activeBrick=new CSBrick;
            else if(brickType==4)
                activeBrick=new CLBrick;
            else if(brickType==5)
                activeBrick=new COBrick;
            else if(brickType==6)
                activeBrick=new CIBrick;
            else if(brickType==7)
                activeBrick=new CJBrick;
              /////////////////
            if(brickType1==1)
                activeBrick1=new CTBrick;
            else if(brickType1==2)
                activeBrick1=new CABrick;
            else if(brickType1==3)
                activeBrick1=new CLBrick;
            else if(brickType1==4)
                activeBrick1=new CSBrick;
            else if(brickType1==5)
                activeBrick1=new COBrick;
            else if(brickType1==6)
                activeBrick1=new CIBrick;
            else if(brickType1==7)
                activeBrick1=new CJBrick;
            }
            activeBrick->setColour((unsigned char)brickType); //左边主界面设置颜色
            activeBrick->putAtTop(initOrientation,binWidth/2);//将产生的砖块置顶
            //-----
            activeBrick1->setColour((unsigned char)brickType1); //左边预测砖块设置颜色
            activeBrick1->putAtMid(initOrientation1,binWidth1/2);//将预测产生的砖块放置在面板中间
            ///******************************************
            notCollide=activeBrick->checkCollision(bin); //判断是否碰撞
            if(notCollide)        //判断是否碰撞
            {
                brickInFlight=1;
                bin->getImage(image);
                activeBrick->operator>>(image);
                bin1->getImage(image1);
                activeBrick1->operator>>(image1);
                this->repaint();
            }
            else              //碰撞则游戏设置游戏结束变量，删除new的东西

            {
                gameOver=1;
                delete activeBrick;
                delete activeBrick1;
                brickInFlight=0;
            }
        }
        if(brickInFlight&&!gameOver)
        {
            if(!Pause1)
            notCollide=activeBrick->shiftDown(bin); //砖块下移一格
            if(notCollide){
                bin->getImage(image);         //不冲突获得画面
                activeBrick->operator>>(image); //显示画面
            }
            else
            {
                brickInFlight=0;
                bin->getImage(image);

                activeBrick->operator>>(image);
                bin->setImage(image);

                this->repaint();
                numLines=numLines+bin->removeFullLines();  //消行分数增加
                bin->getImage(image);

            }
            this->repaint();
        }
        if(gameOver){           //左边游戏是否结束
            killTimer(timerID);

            if(GameModal==2)
            if(QMessageBox::question(this,tr("提示"),tr("左边的兄弟，得加油啊！还玩吗?"),QMessageBox::Yes,QMessageBox::No) == QMessageBox::Yes)
                gameStart();
            else
                close();
            else
                if(QMessageBox::question(this,tr("提示"),tr("兄弟，得加油啊！还玩吗?"),QMessageBox::Yes,QMessageBox::No) == QMessageBox::Yes)
                gameStart();
            else
                close();

        }
        ////////////////////////////////////////////////////
        if(GameModal==2)
        {
        if(!brickInFlight1&&!gameOver1) //右边的显示与判断冲突与左边完全一样
        {

            if(!RandomFlag1)
            {
              brickType2=((unsigned int)qrand()%NUM_BRICK_TYPES)+1;
              initOrientation2=(unsigned int)(qrand()%4);
              RandomFlag1=true;
            }
            else
            {
                brickType2=brickType3;
                initOrientation2=initOrientation3;
            }
            qsrand(QTime::currentTime().msec());                          //以时间为种子生成随机序列
            brickType3=(qrand()%NUM_BRICK_TYPES)+1;
            initOrientation3=(unsigned int)(qrand()%4);



            {
                if(brickType2==1)
                activeBrick2=new CTBrick;
            else if(brickType2==2)
                activeBrick2=new CABrick;
            else if(brickType2==3)
                activeBrick2=new CLBrick;
            else if(brickType2==4)
                activeBrick2=new CSBrick;
            else if(brickType2==5)
                activeBrick2=new COBrick;
            else if(brickType2==6)
                activeBrick2=new CIBrick;
            else if(brickType2==7)
                activeBrick2=new CJBrick;

            ///
            if(brickType3==1)
                activeBrick3=new CTBrick;
            else if(brickType3==2)
                activeBrick3=new CABrick;
            else if(brickType3==3)
                activeBrick3=new CLBrick;
            else if(brickType3==4)
                activeBrick3=new CSBrick;
            else if(brickType3==5)
                activeBrick3=new COBrick;
            else if(brickType3==6)
                activeBrick3=new CIBrick;
            else if(brickType3==7)
                activeBrick3=new CJBrick;
            }

            activeBrick2->setColour((unsigned char)brickType2);
            activeBrick2->putAtTop(initOrientation2,binWidth2/2);
            //-----
            activeBrick3->setColour((unsigned char)brickType3);
            activeBrick3->putAtMid(initOrientation3,binWidth3/2);
            notCollide1=activeBrick2->checkCollision(bin2);
            if(notCollide1)
            {
                brickInFlight1=1;
                bin2->getImage(image2);
                activeBrick2->operator>>(image2);
                bin3->getImage(image3);
                activeBrick3->operator>>(image3);
                this->repaint();
            }
            else

            {
                gameOver1=1;
                delete activeBrick2;
                delete activeBrick3;
                brickInFlight1=0;
            }
        }

        //---------------------------------
        if(brickInFlight1&&!gameOver1)
        {
            if(!Pause2)
            notCollide1=activeBrick2->shiftDown(bin2);
            if(notCollide1){
                bin2->getImage(image2);
                activeBrick2->operator>>(image2);
            }
            else
            {
                brickInFlight1=0;
                bin2->getImage(image2);

                activeBrick2->operator>>(image2);
                bin2->setImage(image2);

                this->repaint();
                numLines1=numLines1+bin2->removeFullLines();
                bin2->getImage(image2);

            }
            this->repaint();
        }
        if(gameOver1){        //右边边游戏是否结束
            killTimer(timerID);

            if(QMessageBox::question(this,tr("提示"),tr("右边的兄弟，得加油啊！还玩吗？"),QMessageBox::Yes,QMessageBox::No) == QMessageBox::Yes)
                gameStart();
            else
                close();
        }
        }
    }
}

void Tetris::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    unsigned int width,i,j;
    unsigned int height,width1,height1;
    unsigned int height2,width2,height3,width3;

    width=bin->getWidth();  //左边主显示面板宽度与高度的获取
    height=bin->getHeight();
    width1=bin1->getWidth();//左边预测面板的宽度与高度的获取
    height1=bin1->getHeight();

    width2=bin2->getWidth();//右边主显示面板宽度与高度的获取
    height2=bin2->getHeight();
    width3=bin3->getWidth();//右边预测面板的宽度与高度的获取
    height3=bin3->getHeight();

    int nSize=20;

    QRect rect(0,0,860,500);
    QImage imageBack;
    imageBack.load(":/images/background.png");
    QBrush brushBack(imageBack);
    painter.setBrush(brushBack);
    painter.drawRect(rect);


    //右边玩家分数的输出
    QRect re;
    //pDC->FillSolidRect(re,RGB(210,255,255));

    char buf[100];

   // sprintf(buf,"  %d  ",numLines*10);
   // pDC->TextOut(330,90,buf);
    ui->label_scorel->setText(QString::number(numLines*10));
    ui->label_scorel_2->setText(QString::number(numLines1*10));
    //左边玩家分数的输出

    QRect  rc,rc1,rc2,rc3;
    QString str[] = {":/images/blue.png",
                       ":/images/red.png",
                       ":/images/green.png",
                       ":/images/blue.png",
                       ":/images/ya.png",
                       ":/images/yello.png"
                       ":/images/green.png",
                       ":/images/green.png"};
    int b,b1,b2;

    for(i=0;i<height1;i++)
    {
        for(j=0;j<width1;j++)
        {
            rc1=QRect(j*nSize+300,i*nSize,nSize,nSize);		//矩形的区域
            if(image1[i][j]!=0)
            {
                b=image1[i][j];
               // qDebug()<<str[b];
                QImage img;
                img.load(":/images/red.png");
               // img.load(str[b]);
                QBrush brush(img);
                painter.setBrush(brush);
                painter.fillRect(rc1,brush);

              //  painter.setBrush(Qt::green);
              //  painter.drawRect(rc1);
            }
        }
    }
    for(i=0;i<height;i++)
    {
        for(j=0;j<width;j++)
        {
            rc=QRect(j*nSize+80,i*nSize,nSize,nSize);
            if(image[i][j]!=0)
            {
                b=image[i][j];    //左边玩家主面板砖块的位图填充
           //     qDebug()<<str[b];
                QImage img;
                img.load(":/images/red.png");
               // img.load(str[b]);
                QBrush brush(img);
                painter.setBrush(brush);
                painter.fillRect(rc,brush);
            }
        }
    }


    /////////////////////////////////////////
    if(GameModal==2)
    {
        for(i=0;i<height3;i++)
        {
            for(j=0;j<width3;j++)
            {
                rc3=QRect(j*nSize+420,i*nSize,nSize,nSize);
                if(image3[i][j]!=0)
                {
                    b=image3[i][j];//右边玩家预测砖块的位图填充
                 //   qDebug()<<str[b];
                    QImage img;
                    img.load(":/images/green.png");
                   // img.load(str[b]);
                    QBrush brush(img);
                    painter.setBrush(brush);
                    painter.fillRect(rc3,brush);
                }
            }
        }
        for(i=0;i<height2;i++)
        {
            for(j=0;j<width2;j++)
            {
                rc2=QRect(j*nSize+540,i*nSize,nSize,nSize);
                if(image2[i][j]!=0)
                {
                    b=image2[i][j];//右边玩家主面板砖块的位图填充
                   // qDebug()<<str[b];
                    QImage img;
                    img.load(":/images/green.png");
                   // img.load(str[b]);
                    QBrush brush(img);
                    painter.setBrush(brush);
                    painter.fillRect(rc2,brush);
                }


            }
        }
    }
}
