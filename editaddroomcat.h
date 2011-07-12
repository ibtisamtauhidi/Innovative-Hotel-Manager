#ifndef EDITADDROOMCAT_H
#define EDITADDROOMCAT_H

#include <QDialog>

namespace Ui {
    class editAddRoomCat;
}

class editAddRoomCat : public QDialog
{
    Q_OBJECT

public:
    explicit editAddRoomCat(QWidget *parent = 0);
    ~editAddRoomCat();

private:
    Ui::editAddRoomCat *ui;


private slots:
    void on_okButton_clicked();
    void on_name_textChanged();
    void on_price_textChanged();


};

#endif // EDITADDROOMCAT_H
