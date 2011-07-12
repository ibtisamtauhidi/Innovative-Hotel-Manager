#ifndef CHECKINFORM_H
#define CHECKINFORM_H

#include <QDialog>

namespace Ui {
    class checkInForm;
}

class checkInForm : public QDialog
{
    Q_OBJECT

public:
    explicit checkInForm(QWidget *parent = 0);
    ~checkInForm();
    void setupview();

private:
    Ui::checkInForm *ui;

public slots:
    void on_catList_currentIndexChanged();
    void on_okButton_clicked();
    void on_roomList_currentIndexChanged();


};

#endif // CHECKINFORM_H
