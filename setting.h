#ifndef SETTING_H
#define SETTING_H

#include <QDialog>

namespace Ui {
    class setting;
}

class setting : public QDialog
{
    Q_OBJECT

public:
    explicit setting(QWidget *parent = 0);
    ~setting();

private:
    Ui::setting *ui;

private slots:
    void on_name_textChanged();
    void on_motto_textChanged();
    void on_ok_clicked();

};

#endif // SETTING_H
