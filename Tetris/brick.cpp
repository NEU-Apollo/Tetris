#include "brick.h"

int CBrick::getOrientation(){ return orientation; }
int CBrick::getPosX(){ return posX; }
int CBrick::getPosY(){ return posY; }
unsigned char CBrick::getColour(){ return colour; }

void CBrick::setOrientation(int newOrient){ orientation = newOrient; }
void CBrick::setPosX(int newPosX){ posX = newPosX; }
void CBrick::setPosY(int newPosY){ posY = newPosY; }
void CBrick::setColour(unsigned char newColour){ colour = newColour; }

//共有I，L，S，O，T，J这6种形状，分别设置左移，下移，右移，旋转，检测碰撞，重载>>运算符以实现输入
int CIBrick::shiftLeft(CBin* bin)
{
    int posX;
    posX=getPosX();
    setPosX(posX-1);
    if (checkCollision(bin)==0) {
        setPosX(posX);
        return 0;
    }
    return 1;
}
int CIBrick::shiftDown(CBin* bin)
{
    int posY;

    posY=getPosY();
    setPosY(posY+1);
    if (checkCollision(bin)== 0) {
        setPosY(posY);
        return 0;
    }
    return 1;
}
int CIBrick::shiftRight(CBin* bin)
{
    int posX;
    posX=getPosX();
    setPosX(posX+1);
    if (checkCollision(bin)==0) {
        setPosX(posX);
        return 0;
    }
    return 1;
}
int CIBrick::rotateClockwise(CBin* bin)
{
    int orientation,oldOrientation;
    orientation=getOrientation();
    oldOrientation=orientation;
    if (orientation==3)
        orientation=0;
    else
        orientation=orientation+1;
    setOrientation(orientation);
    if (checkCollision(bin)==0) {
        setOrientation(oldOrientation);
        return 0;
    }
    return 1;
}

int CIBrick::checkCollision(CBin* bin)
{
    int width;
    int height;
    unsigned char** image;
    int orientation;
    int posX;
    int posY;

    //构建I形状的小方块
    width=bin->getWidth();
    height=bin->getHeight();
    image = new unsigned char* [height];
    for (int i = 0; i<height; i++)
    {
        image[i] = new unsigned char [width];
    }

    bin->getImage(image);
    orientation=getOrientation();
    posX=getPosX();
    posY=getPosY();
    //I-brick状态0
    if (orientation==0)
    {
        //砖块碰到边界
        if(	(posX<0)||
            (posX>width-1)||
            (posY<1)||
            (posY+2>=height))
          return 0;
        //砖块碰到其他固定砖块
        if ( (image[posY-1][posX]!=0)||
             (image[posY][posX]!=0)||
             (image[posY+1][posX]!=0)||
             (image[posY+2][posX]!=0))
             return 0;
    }
    //状态1
    if (orientation==1)
    {
        if( (posX<2)||
            (posX+1>width-1)||
            (posY<0)||
            (posY>height-1))
          return 0;
        if ( (image[posY][posX-2]!=0)||
             (image[posY][posX-1]!=0)||
             (image[posY][posX]!=0)||
             (image[posY][posX+1]!=0))
             return 0;
    }
    //状态 2
    if (orientation==2)
    {
        if((posX<0)||
            (posX>width-1)||
            (posY<2)||
            (posY+1>height-1))
          return 0;
        if ( (image[posY-2][posX]!=0)||
             (image[posY-1][posX]!=0)||
             (image[posY][posX]!=0)||
             (image[posY+1][posX]!=0))
             return 0;
    }
    if (orientation==3)
    {
        if( (posX<1)||
            (posX+2>width-1)||
            (posY<0)||
            (posY>height-1))
          return 0;
        if ( (image[posY][posX-1]!=0)||
             (image[posY][posX]!=0)||
             (image[posY][posX+1]!=0)||
             (image[posY][posX+2]!=0))
             return 0;
    }

    return 1;
}
void CIBrick::operator>>(unsigned char** binImage)
{
    int orientation;
    int posX;
    int posY;
    unsigned char colour;
    posX=getPosX();
    posY=getPosY();
    orientation=getOrientation();
    colour=getColour();
    //状态 0
    if (orientation==0)
    {
        binImage[posY-1][posX]=colour;
        binImage[posY][posX]=colour;
        binImage[posY+1][posX]=colour;
        binImage[posY+2][posX]=colour;
    }
    //状态 1
    if (orientation==1)
    {
        binImage[posY][posX-2]=colour;
        binImage[posY][posX-1]=colour;
        binImage[posY][posX]=colour;
        binImage[posY][posX+1]=colour;
    }
    //状态 2
    if (orientation==2)
    {
        binImage[posY-2][posX]=colour;
        binImage[posY-1][posX]=colour;
        binImage[posY][posX]=colour;
        binImage[posY+1][posX]=colour;
    }
    //状态 3
    if (orientation==3)
    {
        binImage[posY][posX-1]=colour;
        binImage[posY][posX]=colour;
        binImage[posY][posX+1]=colour;
        binImage[posY][posX+2]=colour;
    }
}
void CIBrick::putAtTop(int newOrient, int newPosX)
{
    setPosX(newPosX);
    setOrientation(newOrient);
    switch(newOrient)
    {
    case 0:	setPosY(1); break;
    case 1: setPosY(0); break;
    case 2: setPosY(2); break;
    case 3: setPosY(0); break;
    }
}
void CIBrick::putAtMid(int newOrient, int newPosX)
{
    setPosX(newPosX-3);
    setOrientation(newOrient);
    switch(newOrient)
    {
    case 0:	setPosY(9); break;
    case 1: setPosY(8); break;
    case 2: setPosY(10); break;
    case 3: setPosY(8); break;

    }
}
///////////////////CLBrick /////////////
int CLBrick::shiftLeft(CBin* bin)
{
    int posX;

    posX=getPosX();
    setPosX(posX-1);
    if (checkCollision(bin)== 0) {
        setPosX(posX);
        return 0;
    }

    return 1;
}
int CLBrick::shiftDown(CBin* bin)
{
    int posY;
    posY=getPosY();
    setPosY(posY+1);
    if (checkCollision(bin)== 0) {
        setPosY(posY);
        return 0;
    }
    return 1;
}
int CLBrick::shiftRight(CBin* bin)
{
    int posX;
    posX=getPosX();
    setPosX(posX+1);
    if (checkCollision(bin)==0) {
        setPosX(posX);
        return 0;
    }
    return 1;
}

int CLBrick::rotateClockwise(CBin* bin)
{
    int orientation,oldOrientation;
    orientation=getOrientation();
    oldOrientation=orientation;

    if (orientation==3)
        orientation=0;
    else
        orientation=orientation+1;
    setOrientation(orientation);
    if (checkCollision(bin)== 0) {
        setOrientation(oldOrientation);
        return 0;
    }
    return 1;
}
int CLBrick::checkCollision(CBin* bin)
{
    int width;
    int height;
    unsigned char** image;
    int orientation;
    int posX;
    int posY;
    width=bin->getWidth();
    height=bin->getHeight();
    image = new unsigned char* [height];
    for (int i = 0; i<height; i++)
    {
        image[i] = new unsigned char [width];
    }
    bin->getImage(image);
    orientation=getOrientation();
    posX=getPosX();
    posY=getPosY();
    if (orientation==0)
    {
        if((posX<0)||
            (posX+1>width-1)||
            (posY<1)||
            (posY+1>height-1))
          return 0;
        if ( (image[posY-1][posX]!=0)||
             (image[posY][posX]!=0)||
             (image[posY+1][posX]!=0)||
             (image[posY+1][posX+1]!=0))
             return 0;
    }
    if (orientation==1)
    {
        if( (posX<1)||
            (posX+1>width-1)||
            (posY<0)||
            (posY+1>height-1))
          return 0;
        if ( (image[posY+1][posX-1]!=0)||
             (image[posY][posX-1]!=0)||
             (image[posY][posX]!=0)||
             (image[posY][posX+1]!=0))
             return 0;
    }
    if (orientation==2)
    {
        if( (posX<1)||
            (posX>width-1)||
            (posY<1)||
            (posY+1>height-1))
          return 0;
        if ( (image[posY-1][posX-1]!=0)||
             (image[posY-1][posX]!=0)||
             (image[posY][posX]!=0)||
             (image[posY+1][posX]!=0))
             return 0;
    }
    if (orientation==3)
    {
        if( (posX<1)||
            (posX+1>width-1)||
            (posY<1)||
            (posY>height-1))
          return 0;
        if ( (image[posY][posX-1]!=0)||
             (image[posY][posX]!=0)||
             (image[posY][posX+1]!=0)||
             (image[posY-1][posX+1]!=0))
             return 0;
    }
    return 1;
}
void CLBrick::operator>>(unsigned char** binImage)
{
    int orientation;
    int posX;
    int posY;
    unsigned char colour;
    posX=getPosX();
    posY=getPosY();
    orientation=getOrientation();
    colour=getColour();
    if (orientation==0)
    {
        binImage[posY-1][posX]=colour;
        binImage[posY][posX]=colour;
        binImage[posY+1][posX]=colour;
        binImage[posY+1][posX+1]=colour;
    }
    if (orientation==1)
    {
        binImage[posY+1][posX-1]=colour;
        binImage[posY][posX-1]=colour;
        binImage[posY][posX]=colour;
        binImage[posY][posX+1]=colour;
    }
    if (orientation==2)
    {
        binImage[posY-1][posX-1]=colour;
        binImage[posY-1][posX]=colour;
        binImage[posY][posX]=colour;
        binImage[posY+1][posX]=colour;
    }
    if (orientation==3)
    {
        binImage[posY][posX-1]=colour;
        binImage[posY][posX]=colour;
        binImage[posY][posX+1]=colour;
        binImage[posY-1][posX+1]=colour;
    }
}
void CLBrick::putAtTop(int newOrient, int newPosX)
{
    setPosX(newPosX);
    setOrientation(newOrient);
    switch(newOrient)
    {
    case 0:	setPosY(1); break;
    case 1: setPosY(0); break;
    case 2: setPosY(1); break;
    case 3: setPosY(1); break;

    }
}
void CLBrick::putAtMid(int newOrient, int newPosX)
{
    setPosX(newPosX-3);
    setOrientation(newOrient);
    switch(newOrient)
    {
    case 0:	setPosY(9); break;
    case 1: setPosY(8); break;
    case 2: setPosY(9); break;
    case 3: setPosY(9); break;

    }
}
///////////////////CSBrick /////////////

int CSBrick::shiftLeft(CBin* bin)
{
    int posX;

    posX=getPosX();
    setPosX(posX-1);
    if (checkCollision(bin)== 0) {
        setPosX(posX);
        return 0;
    }
    return 1;
}
int CSBrick::shiftDown(CBin* bin)
{
    int posY;

    posY=getPosY();
    setPosY(posY+1);
    if (checkCollision(bin)== 0) {
        setPosY(posY);
        return 0;
    }
    return 1;
}
int CSBrick::shiftRight(CBin* bin)
{
    int posX;
    posX=getPosX();
    setPosX(posX+1);
    if (checkCollision(bin)==0) {
        setPosX(posX);
        return 0;
    }
    return 1;
}
int CSBrick::rotateClockwise(CBin* bin)
{
    int orientation,oldOrientation;
    orientation=getOrientation();
    oldOrientation=orientation;
    if (orientation==3)
        orientation=0;
    else
        orientation=orientation+1;
    setOrientation(orientation);
    if (checkCollision(bin)== 0) {
        setOrientation(oldOrientation);
        return 0;
    }
    return 1;
}

int CSBrick::checkCollision(CBin* bin)
{
    int width;
    int height;
    unsigned char** image;
    int orientation;
    int posX;
    int posY;
    width=bin->getWidth();
    height=bin->getHeight();
    image = new unsigned char* [height];
    for (int i = 0; i<height; i++)
    {
        image[i] = new unsigned char [width];
    }
    bin->getImage(image);
    orientation=getOrientation();
    posX=getPosX();
    posY=getPosY();
    if (orientation==0)
    {
        if((posX<1)||
            ((posX+1)>width-1)||
            (posY<1)||
            (posY>height-1))
          return 0;
        if ( (image[posY-1][posX]!=0)||
             (image[posY-1][posX+1]!=0)||
             (image[posY][posX]!=0)||
             (image[posY][posX-1]!=0))
             return 0;
    }
    if (orientation==1)
    {
        if( (posX<0)||
            ((posX+1)>width-1)||
            (posY<1)||
            ((posY+1)>height-1))
          return 0;
        if ( (image[posY-1][posX]!=0)||
             (image[posY][posX+1]!=0)||
             (image[posY][posX]!=0)||
             (image[posY+1][posX+1]!=0))
             return 0;
    }
    if (orientation==2)
    {
        if((posX<1)||
            ((posX+1)>width-1)||
            (posY<0)||
            ((posY+1)>height-1))
          return 0;
        if ( (image[posY][posX+1]!=0)||
             (image[posY+1][posX]!=0)||
             (image[posY][posX]!=0)||
             (image[posY+1][posX-1]!=0))
             return 0;
    }
    if (orientation==3)
    {
        if( (posX<1)||
            (posX>width-1)||
            (posY<1)||
            ((posY+1)>height-1))
        return 0;
        if ( (image[posY][posX-1]!=0)||
             (image[posY-1][posX-1]!=0)||
             (image[posY][posX]!=0)||
             (image[posY+1][posX]!=0))
             return 0;
    }
    return 1;
}

void CSBrick::operator>>(unsigned char** binImage)
{
    int orientation;
    int posX;
    int posY;
    unsigned char colour;


    posX=getPosX();
    posY=getPosY();
    orientation=getOrientation();
    colour=getColour();
    if (orientation==0)
    {
        binImage[posY-1][posX]=colour;
        binImage[posY][posX]=colour;
        binImage[posY-1][posX+1]=colour;
        binImage[posY][posX-1]=colour;
    }
    if (orientation==1)
    {
        binImage[posY+1][posX+1]=colour;
        binImage[posY][posX+1]=colour;
        binImage[posY][posX]=colour;
        binImage[posY-1][posX]=colour;
    }
    if (orientation==2)
    {
        binImage[posY][posX+1]=colour;
        binImage[posY+1][posX]=colour;
        binImage[posY][posX]=colour;
        binImage[posY+1][posX-1]=colour;
    }
    if (orientation==3)
    {
        binImage[posY][posX-1]=colour;
        binImage[posY][posX]=colour;
        binImage[posY-1][posX-1]=colour;
        binImage[posY+1][posX]=colour;
    }

}

void CSBrick::putAtTop(int newOrient, int newPosX)
{
    setPosX(newPosX);
    setOrientation(newOrient);
    switch(newOrient)
    {
    case 0:	setPosY(1); break;
    case 1: setPosY(1); break;
    case 2: setPosY(0); break;
    case 3: setPosY(1); break;
    }
}
void CSBrick::putAtMid(int newOrient, int newPosX)
{
    setPosX(newPosX-3);
    setOrientation(newOrient);
    switch(newOrient)
    {
    case 0:	setPosY(9); break;
    case 1: setPosY(9); break;
    case 2: setPosY(8); break;
    case 3: setPosY(9); break;

    }
}
/////////////////COBrick/////////////////
int COBrick::shiftLeft(CBin* bin)
{
    int posX;

    posX=getPosX();
    setPosX(posX-1);
    if (checkCollision(bin)== 0) {
        setPosX(posX);
        return 0;
    }

    return 1;
}
int COBrick::shiftDown(CBin* bin)
{
    int posY;
    posY=getPosY();
    setPosY(posY+1);
    if (checkCollision(bin)== 0) {
        setPosY(posY);
        return 0;
    }
    return 1;
}
int COBrick::shiftRight(CBin* bin)
{
    int posX;
    posX=getPosX();
    setPosX(posX+1);
    if (checkCollision(bin)==0) {
        setPosX(posX);
        return 0;
    }
    return 1;
}

int COBrick::rotateClockwise(CBin* bin)
{
    int orientation,oldOrientation;
    orientation=getOrientation();
    oldOrientation=orientation;

    if (orientation==3)
        orientation=0;
    else
        orientation=orientation+1;
    setOrientation(orientation);
    if (checkCollision(bin)== 0) {
        setOrientation(oldOrientation);
        return 0;
    }
    return 1;
}
int COBrick::checkCollision(CBin* bin)
{
    int width;
    int height;
    unsigned char** image;
    int orientation;
    int posX;
    int posY;
    width=bin->getWidth();
    height=bin->getHeight();
    image = new unsigned char* [height];
    for (int i = 0; i<height; i++)
    {
        image[i] = new unsigned char [width];
    }
    bin->getImage(image);
    orientation=getOrientation();
    posX=getPosX();
    posY=getPosY();
    //状态1
    if (orientation==0)
    {
        if((posX<1)||
            (posX>width-1)||
            (posY<0)||
            (posY+1>height-1))
          return 0;
        if ( (image[posY][posX-1]!=0)||
             (image[posY][posX]!=0)||
             (image[posY+1][posX-1]!=0)||
             (image[posY+1][posX]!=0))
             return 0;
    }
    //状态2
    if (orientation==1)
    {
        if( (posX<1)||
            (posX>width-1)||
            (posY<1)||
            (posY>height-1))
          return 0;
        if ( (image[posY-1][posX-1]!=0)||
             (image[posY-1][posX]!=0)||
             (image[posY][posX-1]!=0)||
             (image[posY][posX]!=0))
             return 0;
    }
    //状态3
    if (orientation==2)
    {
        if( (posX<0)||
            (posX+1>width-1)||
            (posY<1)||
            (posY>height-1))
          return 0;
        if ( (image[posY-1][posX]!=0)||
             (image[posY-1][posX+1]!=0)||
             (image[posY][posX]!=0)||
             (image[posY][posX+1]!=0))
             return 0;
    }
    //状态4
    if (orientation==3)
    {
        if( (posX<0)||
            (posX+1>width-1)||
            (posY<0)||
            (posY+1>height-1))
          return 0;
        if ( (image[posY][posX+1]!=0)||
             (image[posY][posX]!=0)||
             (image[posY+1][posX]!=0)||
             (image[posY+1][posX+1]!=0))
             return 0;
    }
    return 1;
}
void COBrick::operator>>(unsigned char** binImage)
{
    int orientation;
    int posX;
    int posY;
    unsigned char colour;
    posX=getPosX();
    posY=getPosY();
    orientation=getOrientation();
    colour=getColour();
    if (orientation==0)
    {
        binImage[posY][posX-1]=colour;
        binImage[posY][posX]=colour;
        binImage[posY+1][posX-1]=colour;
        binImage[posY+1][posX]=colour;
    }
    if (orientation==1)
    {
        binImage[posY-1][posX-1]=colour;
        binImage[posY-1][posX]=colour;
        binImage[posY][posX-1]=colour;
        binImage[posY][posX]=colour;
    }
    if (orientation==2)
    {
        binImage[posY-1][posX]=colour;
        binImage[posY-1][posX+1]=colour;
        binImage[posY][posX]=colour;
        binImage[posY][posX+1]=colour;
    }
    if (orientation==3)
    {
        binImage[posY][posX+1]=colour;
        binImage[posY][posX]=colour;
        binImage[posY+1][posX]=colour;
        binImage[posY+1][posX+1]=colour;
    }
}
void COBrick::putAtTop(int newOrient, int newPosX)
{
    setPosX(newPosX);
    setOrientation(newOrient);
    switch(newOrient)
    {
    case 0:	setPosY(0); break;
    case 1: setPosY(1); break;
    case 2: setPosY(1); break;
    case 3: setPosY(0); break;

    }
}
void COBrick::putAtMid(int newOrient, int newPosX)
{
    setPosX(newPosX-3);
    setOrientation(newOrient);
    switch(newOrient)
    {
    case 0:	setPosY(8); break;
    case 1: setPosY(9); break;
    case 2: setPosY(9); break;
    case 3: setPosY(8); break;
    }
}
/////////////////CTBrick/////////////////
int CTBrick::shiftLeft(CBin* bin)
{
    int posX;

    posX=getPosX();
    setPosX(posX-1);
    if (checkCollision(bin)== 0) {
        setPosX(posX);
        return 0;
    }

    return 1;
}
int CTBrick::shiftDown(CBin* bin)
{
    int posY;
    posY=getPosY();
    setPosY(posY+1);
    if (checkCollision(bin)== 0) {
        setPosY(posY);
        return 0;
    }
    return 1;
}
int CTBrick::shiftRight(CBin* bin)
{
    int posX;
    posX=getPosX();
    setPosX(posX+1);
    if (checkCollision(bin)==0) {
        setPosX(posX);
        return 0;
    }
    return 1;
}

int CTBrick::rotateClockwise(CBin* bin)
{
    int orientation,oldOrientation;
    orientation=getOrientation();
    oldOrientation=orientation;

    if (orientation==3)
        orientation=0;
    else
        orientation=orientation+1;
    setOrientation(orientation);
    if (checkCollision(bin)== 0) {
        setOrientation(oldOrientation);
        return 0;
    }
    return 1;
}
int CTBrick::checkCollision(CBin* bin)
{
    int width;
    int height;
    unsigned char** image;
    int orientation;
    int posX;
    int posY;
    width=bin->getWidth();
    height=bin->getHeight();
    image = new unsigned char* [height];
    for (int i = 0; i<height; i++)
    {
        image[i] = new unsigned char [width];
    }
    bin->getImage(image);
    orientation=getOrientation();
    posX=getPosX();
    posY=getPosY();
    //状态1
    if (orientation==0)
    {
        if((posX<1)||
            (posX>width-1)||
            (posY<1)||
            (posY+1>height-1))
          return 0;
        if ( (image[posY][posX-1]!=0)||
             (image[posY][posX]!=0)||
             (image[posY+1][posX-1]!=0)||
             (image[posY-1][posX]!=0))
             return 0;
    }
    //状态2
    if (orientation==1)
    {
        if( (posX<1)||
            (posX+1>width-1)||
            (posY<1)||
            (posY>height-1))
          return 0;
        if ( (image[posY-1][posX-1]!=0)||
             (image[posY-1][posX]!=0)||
             (image[posY][posX+1]!=0)||
             (image[posY][posX]!=0))
             return 0;
    }
    //状态3
    if (orientation==2)
    {
        if( (posX<0)||
            (posX+1>width-1)||
            (posY<1)||
            (posY+1>height-1))
          return 0;
        if ( (image[posY+1][posX]!=0)||
             (image[posY-1][posX+1]!=0)||
             (image[posY][posX]!=0)||
             (image[posY][posX+1]!=0))
             return 0;
    }
    //状态4
    if (orientation==3)
    {
        if( (posX<1)||
            (posX+1>width-1)||
            (posY<0)||
            (posY+1>height-1))
          return 0;
        if ( (image[posY+1][posX+1]!=0)||
             (image[posY][posX]!=0)||
             (image[posY+1][posX]!=0)||
             (image[posY+1][posX+1]!=0))
             return 0;
    }
    return 1;
}
void CTBrick::operator>>(unsigned char** binImage)
{
    int orientation;
    int posX;
    int posY;
    unsigned char colour;
    posX=getPosX();
    posY=getPosY();
    orientation=getOrientation();
    colour=getColour();
    if (orientation==0)
    {
        binImage[posY][posX-1]=colour;
        binImage[posY][posX]=colour;
        binImage[posY+1][posX-1]=colour;
        binImage[posY-1][posX]=colour;
    }
    if (orientation==1)
    {
        binImage[posY-1][posX-1]=colour;
        binImage[posY-1][posX]=colour;
        binImage[posY][posX+1]=colour;
        binImage[posY][posX]=colour;
    }
    if (orientation==2)
    {
        binImage[posY+1][posX]=colour;
        binImage[posY-1][posX+1]=colour;
        binImage[posY][posX]=colour;
        binImage[posY][posX+1]=colour;
    }
    if (orientation==3)
    {
        binImage[posY+1][posX+1]=colour;
        binImage[posY][posX]=colour;
        binImage[posY+1][posX]=colour;
        binImage[posY][posX-1]=colour;
    }
}
void CTBrick::putAtTop(int newOrient, int newPosX)
{
    setPosX(newPosX);
    setOrientation(newOrient);
    switch(newOrient)
    {
    case 0:	setPosY(1); break;
    case 1: setPosY(1); break;
    case 2: setPosY(1); break;
    case 3: setPosY(0); break;

    }
}
void CTBrick::putAtMid(int newOrient, int newPosX)
{
    setPosX(newPosX-3);
    setOrientation(newOrient);
    switch(newOrient)
    {
    case 0:	setPosY(9); break;
    case 1: setPosY(9); break;
    case 2: setPosY(9); break;
    case 3: setPosY(8); break;

    }
}
/////////////////CJBrick/////////////////
int CJBrick::shiftLeft(CBin* bin)
{
    int posX;

    posX=getPosX();
    setPosX(posX-1);
    if (checkCollision(bin)== 0) {
        setPosX(posX);
        return 0;
    }

    return 1;
}
int CJBrick::shiftDown(CBin* bin)
{
    int posY;
    posY=getPosY();
    setPosY(posY+1);
    if (checkCollision(bin)== 0) {
        setPosY(posY);
        return 0;
    }
    return 1;
}
int CJBrick::shiftRight(CBin* bin)
{
    int posX;
    posX=getPosX();
    setPosX(posX+1);
    if (checkCollision(bin)==0) {
        setPosX(posX);
        return 0;
    }
    return 1;
}

int CJBrick::rotateClockwise(CBin* bin)
{
    int orientation,oldOrientation;
    orientation=getOrientation();
    oldOrientation=orientation;

    if (orientation==3)
        orientation=0;
    else
        orientation=orientation+1;
    setOrientation(orientation);
    if (checkCollision(bin)== 0) {
        setOrientation(oldOrientation);
        return 0;
    }
    return 1;
}
int CJBrick::checkCollision(CBin* bin)
{
    int width;
    int height;
    unsigned char** image;
    int orientation;
    int posX;
    int posY;
    width=bin->getWidth();
    height=bin->getHeight();
    image = new unsigned char* [height];
    for (int i = 0; i<height; i++)
    {
        image[i] = new unsigned char [width];
    }
    bin->getImage(image);
    orientation=getOrientation();
    posX=getPosX();
    posY=getPosY();
    //状态1
    if (orientation==0)
    {
        if((posX<1)||
            (posX>width-1)||
            (posY<2)||
            (posY>height-1))
          return 0;
        if ( (image[posY][posX-1]!=0)||
             (image[posY][posX]!=0)||
             (image[posY-2][posX]!=0)||
             (image[posY-1][posX]!=0))
             return 0;
    }
    //状态2
    if (orientation==1)
    {
        if( (posX<0)||
            (posX+2>width-1)||
            (posY<1)||
            (posY>height-1))
          return 0;
        if ( (image[posY][posX+2]!=0)||
             (image[posY-1][posX]!=0)||
             (image[posY][posX+1]!=0)||
             (image[posY][posX]!=0))
             return 0;
    }
    //状态3
    if (orientation==2)
    {
        if( (posX<0)||
            (posX+1>width-1)||
            (posY<0)||
            (posY+2>height-1))
          return 0;
        if ( (image[posY+1][posX]!=0)||
             (image[posY+2][posX]!=0)||
             (image[posY][posX]!=0)||
             (image[posY][posX+1]!=0))
             return 0;
    }
    //状态4
    if (orientation==3)
    {
        if( (posX<2)||
            (posX>width-1)||
            (posY<0)||
            (posY+1>height-1))
          return 0;
        if ( (image[posY][posX-1]!=0)||
             (image[posY][posX-2]!=0)||
             (image[posY][posX]!=0)||
             (image[posY+1][posX]!=0))
             return 0;
    }
    return 1;
}
void CJBrick::operator>>(unsigned char** binImage)
{
    int orientation;
    int posX;
    int posY;
    unsigned char colour;
    posX=getPosX();
    posY=getPosY();
    orientation=getOrientation();
    colour=getColour();
    if (orientation==0)
    {
        binImage[posY][posX-1]=colour;
        binImage[posY][posX]=colour;
        binImage[posY-2][posX]=colour;
        binImage[posY-1][posX]=colour;
    }
    if (orientation==1)
    {
        binImage[posY-1][posX]=colour;
        binImage[posY][posX]=colour;
        binImage[posY][posX+1]=colour;
        binImage[posY][posX+2]=colour;
    }
    if (orientation==2)
    {
        binImage[posY+1][posX]=colour;
        binImage[posY][posX+1]=colour;
        binImage[posY+2][posX]=colour;
        binImage[posY][posX]=colour;
    }
    if (orientation==3)
    {
        binImage[posY+1][posX]=colour;
        binImage[posY][posX]=colour;
        binImage[posY][posX-2]=colour;
        binImage[posY][posX-1]=colour;
    }
}
void CJBrick::putAtTop(int newOrient, int newPosX)
{
    setPosX(newPosX);
    setOrientation(newOrient);
    switch(newOrient)
    {
    case 0:	setPosY(2); break;
    case 1: setPosY(1); break;
    case 2: setPosY(0); break;
    case 3: setPosY(0); break;

    }
}
void CJBrick::putAtMid(int newOrient, int newPosX)
{
    setPosX(newPosX-3);
    setOrientation(newOrient);
    switch(newOrient)
    {
    case 0:	setPosY(10); break;
    case 1: setPosY(9); break;
    case 2: setPosY(8); break;
    case 3: setPosY(8); break;

    }
}
/////////////////CABrick/////////////////
int CABrick::shiftLeft(CBin* bin)
{
    int posX;

    posX=getPosX();
    setPosX(posX-1);
    if (checkCollision(bin)== 0) {
        setPosX(posX);
        return 0;
    }

    return 1;
}
int CABrick::shiftDown(CBin* bin)
{
    int posY;
    posY=getPosY();
    setPosY(posY+1);
    if (checkCollision(bin)== 0) {
        setPosY(posY);
        return 0;
    }
    return 1;
}
int CABrick::shiftRight(CBin* bin)
{
    int posX;
    posX=getPosX();
    setPosX(posX+1);
    if (checkCollision(bin)==0) {
        setPosX(posX);
        return 0;
    }
    return 1;
}

int CABrick::rotateClockwise(CBin* bin)
{
    int orientation,oldOrientation;
    orientation=getOrientation();
    oldOrientation=orientation;

    if (orientation==3)
        orientation=0;
    else
        orientation=orientation+1;
    setOrientation(orientation);
    if (checkCollision(bin)== 0) {
        setOrientation(oldOrientation);
        return 0;
    }
    return 1;
}
int CABrick::checkCollision(CBin* bin)
{
    int width;
    int height;
    unsigned char** image;
    int orientation;
    int posX;
    int posY;
    width=bin->getWidth();
    height=bin->getHeight();
    image = new unsigned char* [height];
    for (int i = 0; i<height; i++)
    {
        image[i] = new unsigned char [width];
    }
    bin->getImage(image);
    orientation=getOrientation();
    posX=getPosX();
    posY=getPosY();
    //状态1
    if (orientation==0)
    {
        if((posX<1)||
            (posX+1>width-1)||
            (posY<1)||
            (posY>height-1))
          return 0;
        if ( (image[posY][posX-1]!=0)||
             (image[posY][posX]!=0)||
             (image[posY][posX+1]!=0)||
             (image[posY-1][posX]!=0))
             return 0;
    }
    //状态2
    if (orientation==1)
    {
        if( (posX<0)||
            (posX+1>width-1)||
            (posY<1)||
            (posY+1>height-1))
          return 0;
        if ( (image[posY][posX+1]!=0)||
             (image[posY-1][posX]!=0)||
             (image[posY+1][posX]!=0)||
             (image[posY][posX]!=0))
             return 0;
    }
    //状态3
    if (orientation==2)
    {
        if( (posX<1)||
            (posX+1>width-1)||
            (posY<0)||
            (posY+1>height-1))
          return 0;
        if ( (image[posY+1][posX]!=0)||
             (image[posY][posX]!=0)||
             (image[posY][posX-1]!=0)||
             (image[posY][posX+1]!=0))
             return 0;
    }
    //状态4
    if (orientation==3)
    {
        if( (posX<1)||
            (posX>width-1)||
            (posY<1)||
            (posY+1>height-1))
          return 0;
        if ( (image[posY][posX-1]!=0)||
             (image[posY-1][posX]!=0)||
             (image[posY][posX]!=0)||
             (image[posY+1][posX]!=0))
             return 0;
    }
    return 1;
}
void CABrick::operator>>(unsigned char** binImage)
{
    int orientation;
    int posX;
    int posY;
    unsigned char colour;
    posX=getPosX();
    posY=getPosY();
    orientation=getOrientation();
    colour=getColour();
    if (orientation==0)
    {
        binImage[posY][posX-1]=colour;
        binImage[posY][posX]=colour;
        binImage[posY][posX+1]=colour;
        binImage[posY-1][posX]=colour;
    }
    if (orientation==1)
    {
        binImage[posY-1][posX]=colour;
        binImage[posY][posX]=colour;
        binImage[posY][posX+1]=colour;
        binImage[posY+1][posX]=colour;
    }
    if (orientation==2)
    {
        binImage[posY+1][posX]=colour;
        binImage[posY][posX+1]=colour;
        binImage[posY][posX-1]=colour;
        binImage[posY][posX]=colour;
    }
    if (orientation==3)
    {
        binImage[posY+1][posX]=colour;
        binImage[posY][posX]=colour;
        binImage[posY-1][posX]=colour;
        binImage[posY][posX-1]=colour;
    }
}
void CABrick::putAtTop(int newOrient, int newPosX)
{
    setPosX(newPosX);
    setOrientation(newOrient);
    switch(newOrient)
    {
    case 0:	setPosY(1); break;
    case 1: setPosY(1); break;
    case 2: setPosY(0); break;
    case 3: setPosY(1); break;

    }
}
void CABrick::putAtMid(int newOrient, int newPosX)
{
    setPosX(newPosX-3);
    setOrientation(newOrient);
    switch(newOrient)
    {
    case 0:	setPosY(9); break;
    case 1: setPosY(9); break;
    case 2: setPosY(8); break;
    case 3: setPosY(9); break;

    }
}
//////////////////////////////////////
