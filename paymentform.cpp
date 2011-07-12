#include "paymentform.h"
#include "ui_paymentform.h"

paymentForm::paymentForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::paymentForm)
{
    ui->setupUi(this);
}

paymentForm::~paymentForm()
{
    delete ui;
}
