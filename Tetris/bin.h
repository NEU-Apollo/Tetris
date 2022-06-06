#ifndef CBIN_H
#define CBIN_H

class CBin {//CBin作为填充界面的每个小方格
    private:
        unsigned char** image;//?????
        unsigned int width;//界面的宽度
        unsigned int height;//界面的高度

    public:
        CBin(unsigned int w, unsigned int h);
        ~CBin();

        unsigned int getWidth();//得到宽度
        unsigned int getHeight();//得到高度

        void getImage(unsigned char** destImage);
        void setImage(unsigned char** srcImage);

        unsigned int removeFullLines();//销毁一整行
};

#endif // CBIN_H
