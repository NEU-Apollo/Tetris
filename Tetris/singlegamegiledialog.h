#ifndef SINGLEGAMEGILEDIALOG_H
#define SINGLEGAMEGILEDIALOG_H

#include <QDialog>

namespace Ui {
class SingleGameGileDialog;
}

class SingleGameGileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SingleGameGileDialog(QWidget *parent = nullptr);
    ~SingleGameGileDialog();
    void keyPressEvent(QKeyEvent *e);

private slots:
    void on_lineEdit_editingFinished();

private:
    Ui::SingleGameGileDialog *ui;
};

#endif // SINGLEGAMEGILEDIALOG_H
