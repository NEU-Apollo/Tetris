#ifndef SINGLERANK_H
#define SINGLERANK_H

#include <QWidget>
#include <QDialog>
namespace Ui {
class SingleRank;
}

class SingleRank : public QWidget
{
    Q_OBJECT

public:
    explicit SingleRank(QWidget *parent = nullptr);
    ~SingleRank();

private:
    Ui::SingleRank *ui;
};

#endif // SINGLERANK_H
