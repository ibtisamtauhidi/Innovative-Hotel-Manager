#ifndef EDITRESTAURANT_H
#define EDITRESTAURANT_H

#include <QDialog>

namespace Ui {
    class editRestaurant;
}
class editAddRestaurant;
class editRemRestaurant;
class editRestaurant : public QDialog
{
    Q_OBJECT

public:
    explicit editRestaurant(QWidget *parent = 0);
    ~editRestaurant();

private:
    Ui::editRestaurant *ui;
    editAddRestaurant *InnOeARes;
    editRemRestaurant *InnOeRRes;
    void setupview();

private slots:
    void on_addItem_clicked();
    void on_removeItem_clicked();
    void on_okButton_clicked();
    void setupviewagain();
};

#endif // EDITRESTAURANT_H
