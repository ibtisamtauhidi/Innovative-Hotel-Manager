#ifndef EDITROOMCAT_H
#define EDITROOMCAT_H

#include <QDialog>

namespace Ui {
    class editRoomCat;
}
class editAddRoomCat;
class editRoomCat : public QDialog
{
    Q_OBJECT

public:
    explicit editRoomCat(QWidget *parent = 0);
    ~editRoomCat();
    void setupView();

private:
    Ui::editRoomCat *ui;
    editAddRoomCat *InnOeARCat;

private slots:
    void on_addCat_clicked();
    void on_rmCat_clicked();
    void on_catList_currentTextChanged();
    void on_okButton_clicked();
    void setupviewagain();
};

#endif // EDITROOMCAT_H
