#ifndef TETRIS_H
#define TETRIS_H

#include <QMainWindow>
#include <QKeyEvent>
#include <bin.h>
#include <brick.h>
#include <QWidget>
namespace Ui {
class Tetris;
}

class Tetris : public QMainWindow
{
    Q_OBJECT

public:
    explicit Tetris(QWidget *parent = 0);
    ~Tetris();

private:
    Ui::Tetris *ui;

    CBin *bin,*bin1,*bin2,*bin3;//组成每个小方块的四个最小单元
    CBrick *activeBrick,*activeBrick1,*activeBrick2,*activeBrick3;//前两个是一组，作为玩家一的小方块，一个在主界面中，另一个在提示栏显示
    int gameOver,gameOver1;
    int brickInFlight,brickInFlight1;//????
    int brickType,brickType1,brickType2,brickType3;//小方块的形状
    unsigned int initOrientation,initOrientation1,initOrientation2,initOrientation3;
    int notCollide,notCollide1;//没有碰撞
    unsigned int numLines,numLines1;//????
    unsigned char**image,**image1;
    unsigned char**image2,**image3;
    int difficulty;//设置游戏难度
    int GameModal;//设置游戏模式
    int timerID;//设置定时器，关于小方块以什么速度自动下降

    bool RandomFlag,RandomFlag1;//
    bool Pause1,Pause2;//左面暂停，右面暂停
    bool p;//判断双人界面是否暂停
    bool Flag;//
    bool modal;//

    void init();

public slots:

    void gameStart();//游戏开始
    void onPause();//游戏结束
    //设置游戏难度
    void onDiffEasy();
    void onDiffMid();
    void onDiffSup();
    //void returnmainmenu();
protected:
    void keyPressEvent(QKeyEvent *event);
    void timerEvent(QTimerEvent *event);//定时器用于小方块自动下降
    void paintEvent(QPaintEvent *event);//????

};

#endif // TETRIS_H
