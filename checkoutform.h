#ifndef CHECKOUTFORM_H
#define CHECKOUTFORM_H

#include <QDialog>

namespace Ui {
    class checkOutForm;
}

class checkOutForm : public QDialog
{
    Q_OBJECT

public:
    explicit checkOutForm(QWidget *parent = 0);
    ~checkOutForm();
    void updateShits();

private:
    Ui::checkOutForm *ui;


private slots:
    void on_roomNo_currentIndexChanged();
    void on_payButton_clicked();
    void on_coButton_clicked();

};

#endif // CHECKOUTFORM_H
