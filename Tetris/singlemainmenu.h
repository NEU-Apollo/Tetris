#ifndef SINGLEMAINMENU_H
#define SINGLEMAINMENU_H

#include <QWidget>

namespace Ui {
class SingleMainMenu;
}

class SingleMainMenu : public QWidget
{
    Q_OBJECT

public:
    explicit SingleMainMenu(QWidget *parent = nullptr);
    ~SingleMainMenu();
    void returnmainmenu();

private:
    Ui::SingleMainMenu *ui;
};

#endif // SINGLEMAINMENU_H
