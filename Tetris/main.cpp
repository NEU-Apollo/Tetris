#include "tetris.h"
#include "widget.h"
#include <QApplication>
#include <QMediaPlayer>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget w;
    QMediaPlayer *player = new QMediaPlayer;
            //connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(postitionChanged(qint64)));
            //player->setMedia(QUrl::fromLocalFile("/F:/qt_project/tetris/music/Faded.mp3"));
    player->setMedia(QUrl::fromLocalFile("F:/qt_project/Tetris/music/River.mp3"));
    player->setVolume(40);
    player->play();
    w.setWindowTitle("Tetris");
    w.setWindowIcon(QIcon("F:\\qt_project\\Tetris\\images\\Tetris.ico"));
    w.show();
    return a.exec();
}
