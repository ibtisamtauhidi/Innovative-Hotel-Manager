#ifndef ROOMSPERCAT_H
#define ROOMSPERCAT_H

#include <QDialog>

namespace Ui {
    class roomsPerCat;
}

class roomsPerCat : public QDialog
{
    Q_OBJECT

public:
    explicit roomsPerCat(QWidget *parent = 0);
    ~roomsPerCat();

private:
    Ui::roomsPerCat *ui;

private slots:
    void on_ok_clicked();

};

#endif // ROOMSPERCAT_H
