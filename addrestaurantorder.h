#ifndef ADDRESTAURANTORDER_H
#define ADDRESTAURANTORDER_H

#include <QDialog>

namespace Ui {
    class addRestaurantOrder;
}

class addRestaurantOrder : public QDialog
{
    Q_OBJECT

public:
    explicit addRestaurantOrder(QWidget *parent = 0);
    ~addRestaurantOrder();


private:
    Ui::addRestaurantOrder *ui;

private slots:
    void on_roomNo_currentIndexChanged();
    void on_item_currentIndexChanged();
    void on_addButton_clicked();
    void on_okButton_clicked();
};

#endif // ADDRESTAURANTORDER_H
