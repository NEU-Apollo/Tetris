#ifndef SINGLEGAME_H
#define SINGLEGAME_H

#include <QWidget>
#include <QKeyEvent>

namespace Ui {
class SingleGame;
}

class SingleGame : public QWidget
{
    Q_OBJECT

public:
    explicit SingleGame(QWidget *parent = nullptr);
    ~SingleGame();
    int get_random_number();
    void create_shape(int now_shape);
    void addScore(int,int);
    void addScoreinFile();

    int main_matrix[10][20];
    int now_shape=8;//当前的形状
    int next_shape=8;
    int now_shape_num;//当前形状的状态
    int now_shape_pos1X;//当前形状的位置
    int now_shape_pos1Y;
    int now_shape_pos2X;
    int now_shape_pos2Y;
    int score=0;
    int over_flag;
private:
    Ui::SingleGame *ui;

protected:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);
};

#endif // SINGLEGAME_H
