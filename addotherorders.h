#ifndef ADDOTHERORDERS_H
#define ADDOTHERORDERS_H

#include <QDialog>

namespace Ui {
    class addOtherOrders;
}

class addOtherOrders : public QDialog
{
    Q_OBJECT

public:
    explicit addOtherOrders(QWidget *parent = 0);
    ~addOtherOrders();

private:
    Ui::addOtherOrders *ui;


private slots:
    void on_roomNo_currentIndexChanged();
    void on_okButton_clicked();
    void on_name_textChanged();
    void on_price_textChanged();

};

#endif // ADDOTHERORDERS_H
