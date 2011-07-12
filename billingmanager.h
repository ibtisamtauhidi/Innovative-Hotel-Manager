#ifndef BILLINGMANAGER_H
#define BILLINGMANAGER_H

#include <QDialog>

namespace Ui {
    class billingManager;
}
class billingManager : public QDialog
{
    Q_OBJECT

public:
    explicit billingManager(QWidget *parent = 0);
    ~billingManager();
    void setupview();
    void updatetable();
private:
    Ui::billingManager *ui;

private slots:
    void on_okButton_clicked();
    void on_roomNo_currentIndexChanged();
    void on_payButton_clicked();
    void on_payForm_textChanged();
};

#endif // BILLINGMANAGER_H
