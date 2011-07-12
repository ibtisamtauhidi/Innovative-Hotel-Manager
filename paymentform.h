#ifndef PAYMENTFORM_H
#define PAYMENTFORM_H

#include <QDialog>

namespace Ui {
    class paymentForm;
}

class paymentForm : public QDialog
{
    Q_OBJECT

public:
    explicit paymentForm(QWidget *parent = 0);
    ~paymentForm();

private:
    Ui::paymentForm *ui;
};

#endif // PAYMENTFORM_H
