#ifndef SETDIALOG_H
#define SETDIALOG_H

#include <QDialog>

namespace Ui {
class SetDialog;
}

class SetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetDialog(QWidget *parent = nullptr);
    ~SetDialog();
    void slotOk();
    int getmusic();
    int getlevel();
private:
    int music;
    int level;
    Ui::SetDialog *ui;
};

#endif // SETDIALOG_H
