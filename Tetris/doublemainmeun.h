#ifndef DOUBLEMAINMEUN_H
#define DOUBLEMAINMEUN_H

#include <QWidget>

namespace Ui {
class DoubleMainMeun;
}

class DoubleMainMeun : public QWidget
{
    Q_OBJECT

public:
    explicit DoubleMainMeun(QWidget *parent = nullptr);
    ~DoubleMainMeun();
    void returnmainmenu();
    //void startScene();
private:
    Ui::DoubleMainMeun *ui;
};

#endif // DOUBLEMAINMEUN_H
