#ifndef EDITADDRESTAURANT_H
#define EDITADDRESTAURANT_H

#include <QDialog>

namespace Ui {
    class editAddRestaurant;
}

class editAddRestaurant : public QDialog
{
    Q_OBJECT

public:
    explicit editAddRestaurant(QWidget *parent = 0);
    ~editAddRestaurant();

private:
    Ui::editAddRestaurant *ui;

private slots:
    void on_okButton_clicked();
    void on_name_textChanged();
    void on_price_textChanged();
};

#endif // EDITADDRESTAURANT_H
