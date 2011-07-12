#ifndef EDITREMRESTAURANT_H
#define EDITREMRESTAURANT_H

#include <QDialog>

namespace Ui {
    class editRemRestaurant;
}

class editRemRestaurant : public QDialog
{
    Q_OBJECT

public:
    explicit editRemRestaurant(QWidget *parent = 0);
    ~editRemRestaurant();

private:
    Ui::editRemRestaurant *ui;

private slots:
    void on_okButton_clicked();
};

#endif // EDITREMRESTAURANT_H
