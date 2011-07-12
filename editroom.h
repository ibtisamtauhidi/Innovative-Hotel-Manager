#ifndef EDITROOM_H
#define EDITROOM_H

#include <QDialog>

namespace Ui {
    class editRoom;
}

class editRoom : public QDialog
{
    Q_OBJECT

public:
    explicit editRoom(QWidget *parent = 0);
    ~editRoom();
    void setupview();

private:
    Ui::editRoom *ui;

private slots:
    void on_roomName_textChanged();
    void on_addButton_clicked();
    void on_catList_currentIndexChanged();
    void on_okButton_clicked();
};

#endif // EDITROOM_H
