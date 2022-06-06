
#include "bin.h"


CBin::CBin(unsigned int w, unsigned int h)//????
{
    width=w;
    height=h;
    image = new unsigned char* [height];
    for (unsigned int i = 0; i<height; i++)
    {
        image[i] = new unsigned char [width];
        for (unsigned int j = 0; j<width; j++)
            image[i][j]=0;//设置为0就是没有图片
    }
}
CBin::~CBin()
{
    for (unsigned int i=0; i<height; i++) {
        delete []image[i];
    }
    delete[] image;
}
unsigned int CBin::getWidth()
{ return width; }

unsigned int CBin::getHeight()
{ return height; }

//获取图片，二维格式的
void CBin::getImage(unsigned char** destImage)
{
     for (unsigned int i = 0; i<height; i++)
         for (unsigned int j = 0; j<width; j++)
            destImage[i][j]=image[i][j];
}

//设置图片
void CBin::setImage(unsigned char** srcImage)
{
       for (unsigned int i = 0; i<height; i++)
         for (unsigned int j = 0; j<width; j++)
            image[i][j]=srcImage[i][j];

}
unsigned int CBin::removeFullLines()
{
    unsigned int flag,EmptyLine=0;
    //flag用于标志是否满行，0则满行，1则未满
    unsigned int i,j,m;
    for (i=0; i<height; i++)
    {
        flag=0;
        for (j=0; j<width; j++)
        {
            if (image[i][j]==0 )
            {
                flag=1;break;
            }
        }
        //一行完全被填满
        if(flag==0)
        {
            /*for (j=0; j<width; j++)
            {
                image[i][j]=0;
            }*/
            //下面的所有行向下移动一位
            for(m=i; m>0; m--)
            {
                for (j=0; j<width; j++)
                {
                   image[m][j]=image[m-1][j];//坐标向下越来越大
                }
            }
            /*for (j=0; j<width; j++)
            {
                   image[0][j]=0;
            }*/
            EmptyLine++;  //记录消的行数
            i--;
        }
    }
     return EmptyLine;
}
