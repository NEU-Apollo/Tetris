#ifndef BRICK_H
#define BRICK_H
#include "bin.h"

class CBrick {//方块基类
    protected:
        int orientation;//初始的方向
        int posX;
        int posY;
        unsigned char colour;//小方块的颜色

    public:
        int getOrientation();
        int getPosX();
        int getPosY();
        unsigned char getColour();

        void setOrientation(int newOrient);//设置小方块初始的方向
        void setPosX(int newPosX);
        void setPosY(int newPosY);
        void setColour(unsigned char newColour);

        //按键操作函数
        virtual int shiftLeft(CBin* bin)=0;
        virtual int shiftRight(CBin* bin)=0;
        virtual int shiftDown(CBin* bin)=0;
        virtual int rotateClockwise(CBin* bin)=0;

        //检查方块之间是否发生了碰撞
        virtual int checkCollision(CBin* bin)=0;//发生碰撞返回0

        virtual void operator>>(unsigned char** binImage)=0;//
        virtual void putAtTop(int newOrient, int newPosX)=0;//
        virtual void putAtMid(int newOrient, int newPosX)=0;//
};


class CIBrick : public CBrick {
    public:
        int shiftLeft(CBin* bin);
        int shiftRight(CBin* bin);
        int shiftDown(CBin* bin);
        int rotateClockwise(CBin* bin);

        int checkCollision(CBin* bin);

        void operator>>(unsigned char** binImage);
        void putAtTop(int newOrient, int newPosX);
        void putAtMid(int newOrient, int newPosX);

};
class CLBrick : public CBrick {
    public:
        int shiftLeft(CBin* bin);
        int shiftRight(CBin* bin);
        int shiftDown(CBin* bin);
        int rotateClockwise(CBin* bin);

        int checkCollision(CBin* bin);

        void operator>>(unsigned char** binImage);
        void putAtTop(int newOrient, int newPosX);
        void putAtMid(int newOrient, int newPosX);
};
class CSBrick : public CBrick {
    public:
        int shiftLeft(CBin* bin);
        int shiftRight(CBin* bin);
        int shiftDown(CBin* bin);
        int rotateClockwise(CBin* bin);

        int checkCollision(CBin* bin);

        void operator>>(unsigned char** binImage);
        void putAtTop(int newOrient, int newPosX);
        void putAtMid(int newOrient, int newPosX);
};
class COBrick : public CBrick {
    public:
        int shiftLeft(CBin* bin);
        int shiftRight(CBin* bin);
        int shiftDown(CBin* bin);
        int rotateClockwise(CBin* bin);

        int checkCollision(CBin* bin);

        void operator>>(unsigned char** binImage);
        void putAtTop(int newOrient, int newPosX);
        void putAtMid(int newOrient, int newPosX);
};
class CTBrick : public CBrick {
    public:
        int shiftLeft(CBin* bin);
        int shiftRight(CBin* bin);
        int shiftDown(CBin* bin);
        int rotateClockwise(CBin* bin);

        int checkCollision(CBin* bin);

        void operator>>(unsigned char** binImage);
        void putAtTop(int newOrient, int newPosX);
        void putAtMid(int newOrient, int newPosX);
};
class CJBrick : public CBrick {
    public:
        int shiftLeft(CBin* bin);
        int shiftRight(CBin* bin);
        int shiftDown(CBin* bin);
        int rotateClockwise(CBin* bin);

        int checkCollision(CBin* bin);

        void operator>>(unsigned char** binImage);
        void putAtTop(int newOrient, int newPosX);
        void putAtMid(int newOrient, int newPosX);
};
class CABrick : public CBrick {
    public:
        int shiftLeft(CBin* bin);
        int shiftRight(CBin* bin);
        int shiftDown(CBin* bin);
        int rotateClockwise(CBin* bin);

        int checkCollision(CBin* bin);

        void operator>>(unsigned char** binImage);
        void putAtTop(int newOrient, int newPosX);
        void putAtMid(int newOrient, int newPosX);
};
#endif // BRICK_H
