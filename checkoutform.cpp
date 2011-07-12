#include "checkoutform.h"
#include "ui_checkoutform.h"
#include <QtSql>
#include <QDebug>

checkOutForm::checkOutForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::checkOutForm)
{

    ui->setupUi(this);
    ui->roomNo->addItem(":: select one ::");
    QSqlDatabase db = QSqlDatabase::addDatabase( "QSQLITE" );

    db.setDatabaseName( "./innovativedb.db" );

    if( !db.open() )
    {
        qDebug() << db.lastError();
        qFatal( "Failed to connect." );
    }

    qDebug( "Connected!" );

    QSqlQuery qry;
    qry.prepare("CREATE TABLE IF NOT EXISTS roomlist (id INTEGET PRIMARY KEY, roomno VARCHAR(5), cat INTEGER, occupied INTEGER)");
    if(!qry.exec())
        qDebug() << qry.lastError();
    else
        qDebug( "Room Table Validated..." );

    qry.prepare("SELECT roomno FROM roomlist WHERE occupied <> 0");
    if(!qry.exec())
        qDebug() << qry.lastError();
    else
        qDebug( "Room Table Validated..." );

    while (qry.next()) {
        QString roomno = qry.value(0).toString();
        ui->roomNo->addItem(roomno);
    }
}

checkOutForm::~checkOutForm()
{
    delete ui;
}
void checkOutForm::on_roomNo_currentIndexChanged()
{

    updateShits();
}

void checkOutForm::on_coButton_clicked()
{

    QString roomStr = ui->roomNo->currentText();
    int roomno = roomStr.toInt();

    QSqlDatabase db = QSqlDatabase::addDatabase( "QSQLITE" );

    db.setDatabaseName( "./innovativedb.db" );

    if( !db.open() )
    {
        qDebug() << db.lastError();
        qFatal( "Failed to connect." );
    }

    qDebug( "Connected!" );

    QSqlQuery qry;
    qry.prepare("CREATE TABLE IF NOT EXISTS roomlist (id INTEGET PRIMARY KEY, roomno VARCHAR(5), cat INTEGER, occupied INTEGER)");
    if(!qry.exec())
        qDebug() << qry.lastError();
    else
        qDebug( "Room Table Validated..." );

    qry.prepare("SELECT occupied FROM roomlist WHERE roomno=:room");
    qry.bindValue(":room",roomno);
    if(!qry.exec())
        qDebug() << qry.lastError();
    else
        qDebug( "Room Table Validated..." );

    QString guestID = "";
    while(qry.next())
    {
        guestID = qry.value(0).toString();
    }
    qDebug()<<guestID;

    qry.prepare("CREATE TABLE IF NOT EXISTS guestlist ( id INTEGET PRIMARY KEY, name VARCHAR(30),address VARCHAR(30), nationality VARCHAR(15), phone VARCHAR(15), occupation VARCHAR(15),purpose VARCHAR(20), occupant INTEGER, room VARCHAR(8), intime VARCHAR(30), outtime VARCHAR(30) )");
    if(!qry.exec())
        qDebug() << qry.lastError();
    else
        qDebug( "Table Created!" );


    qry.prepare("UPDATE roomlist SET occupied=0 WHERE roomno=:room");
    qry.bindValue(":room",roomno);
    if(!qry.exec())
         qDebug() << qry.lastError();
    else
         qDebug( "updated roomlist!" );


    QDateTime QDTime = QDateTime::currentDateTime();
    QString QDTStr = QDTime.toString();


    qry.prepare("UPDATE guestlist SET outtime = :time WHERE id=:room");
    qry.bindValue(":time",QDTStr);
    qry.bindValue(":room",guestID);
    if(!qry.exec())
         qDebug() << qry.lastError();
    else
         qDebug( "updated guest record!" );

    this->close();
}

void checkOutForm::on_payButton_clicked()
{
    QString balStr = ui->bal->text();

    QString roomno = ui->roomNo->currentText();

    if(roomno==":: select one ::")
    {
        return;
    }


    QSqlDatabase db = QSqlDatabase::addDatabase( "QSQLITE" );

    db.setDatabaseName( "./innovativedb.db" );

    if( !db.open() )
    {
        qDebug() << db.lastError();
        qFatal( "Failed to connect." );
    }

    qDebug( "Connected!" );

    QSqlQuery qry;
    qry.prepare("CREATE TABLE IF NOT EXISTS roomlist (id INTEGET PRIMARY KEY, roomno VARCHAR(5), cat INTEGER, occupied INTEGER)");
    if(!qry.exec())
        qDebug() << qry.lastError();
    else
        qDebug( "Room Table Validated..." );

    qry.prepare("SELECT occupied FROM roomlist WHERE roomno=:room");
    qry.bindValue(":room",roomno);
    if(!qry.exec())
        qDebug() << qry.lastError();
    else
        qDebug( "Room Table Validated..." );

    QString guestID = "";
    while(qry.next())
    {
        guestID = qry.value(0).toString();
    }

    qry.prepare("CREATE TABLE IF NOT EXISTS guestlist ( id INTEGET PRIMARY KEY, name VARCHAR(30),address VARCHAR(30), nationality VARCHAR(15), phone VARCHAR(15), occupation VARCHAR(15),purpose VARCHAR(20), occupant INTEGER, room VARCHAR(8), intime VARCHAR(30), outtime VARCHAR(30) )");
    if(!qry.exec())
        qDebug() << qry.lastError();
    else
        qDebug( "Table Created!" );

    qry.prepare("CREATE TABLE IF NOT EXISTS payments ( id INTEGET PRIMARY KEY, time VARCHAR(25), amount INTEGER, guestID INTEGER )");
    if(!qry.exec())
        qDebug() << qry.lastError();
    else
        qDebug( "Room Table Validated..." );




    int id=0;
    qry.prepare("SELECT id FROM payments");
    if(!qry.exec())
        qDebug() << qry.lastError();
    else
        qDebug( "Room Table Validated..." );

    while (qry.next()) {
        int cur_item = qry.value(0).toInt();
        if(cur_item > id)
        {
            id=cur_item;
        }
    }
    id++;

    QDateTime QDTime = QDateTime::currentDateTime();
    QString QDTStr = QDTime.toString();

    qry.prepare("INSERT INTO payments ( id, time, amount, guestID ) VALUES (:id, :time, :amount, :guestid )");
    qry.bindValue(":id",id);
    qry.bindValue(":time",QDTStr);
    qry.bindValue(":amount",balStr);
    qry.bindValue(":guestid",guestID);
    if(!qry.exec())
        qDebug() << qry.lastError();
    else
        qDebug( "Room Table Validated..." );

    updateShits();
    ui->coButton->setEnabled(1);

}

void checkOutForm::updateShits()
{
    QString roomno = ui->roomNo->currentText();
     if(roomno==":: select one ::")
     {
        ui->coButton->setEnabled(0);
        ui->name->setText("-");
        ui->totalBill->setText("-");
        ui->bal->setText("-");
        ui->payBill->setText("-");
        ui->payButton->setEnabled(0);
         return;
     }

     QSqlDatabase db = QSqlDatabase::addDatabase( "QSQLITE" );

     db.setDatabaseName( "./innovativedb.db" );

     if( !db.open() )
     {
         qDebug() << db.lastError();
         qFatal( "Failed to connect." );
     }

     qDebug( "Connected!" );

     QSqlQuery qry;
     qry.prepare("CREATE TABLE IF NOT EXISTS roomlist (id INTEGET PRIMARY KEY, roomno VARCHAR(5), cat INTEGER, occupied INTEGER)");
     if(!qry.exec())
         qDebug() << qry.lastError();
     else
         qDebug( "Room Table Validated..." );

     qry.prepare("SELECT occupied FROM roomlist WHERE roomno=:room");
     qry.bindValue(":room",roomno);
     if(!qry.exec())
         qDebug() << qry.lastError();
     else
         qDebug( "Room Table Validated..." );

     QString guestID = "";
     while(qry.next())
     {
         guestID = qry.value(0).toString();
     }
     qDebug()<<guestID;
     qry.prepare("CREATE TABLE IF NOT EXISTS guestlist ( id INTEGET PRIMARY KEY, name VARCHAR(30),address VARCHAR(30), nationality VARCHAR(15), phone VARCHAR(15), occupation VARCHAR(15),purpose VARCHAR(20), occupant INTEGER, room VARCHAR(8), intime VARCHAR(30), outtime VARCHAR(30) )");
     if(!qry.exec())
         qDebug() << qry.lastError();
     else
         qDebug( "Table Created!" );

     qry.prepare("SELECT name,intime FROM guestlist WHERE id=:guestID");
     qry.bindValue(":guestID",guestID);

     if(!qry.exec())
     {
        qDebug() << qry.lastError();
     }
     else
         qDebug( "Table Selected!" );

     while (qry.next())
     {
         QString cur_item = qry.value(0).toString();
         QString cintime = qry.value(1).toString();
         ui->name->setText(cur_item);
         ui->checkInTime->setText(cintime);
         ui->payButton->setEnabled(1);
     }


     qry.prepare("CREATE TABLE IF NOT EXISTS guestlist ( id INTEGET PRIMARY KEY, name VARCHAR(30),address VARCHAR(30), nationality VARCHAR(15), phone VARCHAR(15), occupation VARCHAR(15),purpose VARCHAR(20), occupant INTEGER, room VARCHAR(8), intime VARCHAR(30), outtime VARCHAR(30) )");
     if(!qry.exec())
         qDebug() << qry.lastError();
     else
         qDebug( "Table Created!" );

     qry.prepare("SELECT name FROM guestlist WHERE id=:guestID");
     qry.bindValue(":guestID",guestID);
     if(!qry.exec())
     {
        qDebug() << qry.lastError();
     }
     else
         qDebug( "Table Selected!" );

     while (qry.next())
     {
         QString cur_item = qry.value(0).toString();
         ui->name->setText(cur_item);
     }


     qry.prepare("CREATE TABLE IF NOT EXISTS otherorders (id INTEGER PRIMARY KEY, time VARCHAR(30), text VARCHAR(40), price INTEGER, guestid INTEGER)");
     if(!qry.exec())
         qDebug() << qry.lastError();
     else
         qDebug( "Room Table Validated..." );


     qry.prepare("SELECT price FROM otherorders WHERE guestid = :guestID");
     qry.bindValue(":guestid",guestID);
     if(!qry.exec())
         qDebug() << qry.lastError();
     else
         qDebug( "Room Table Validated..." );

     int totalPrice = 0;
     while (qry.next()) {
         int price = qry.value(0).toInt();
         totalPrice+=price;
     }

     qry.prepare("CREATE TABLE IF NOT EXISTS restorders (id INTEGET PRIMARY KEY, item VARCHAR(20), quantity INTEGER, price INTEGER, guestID INTEGER, time VARCHAR(20))");
     if(!qry.exec())
         qDebug() << qry.lastError();
     else
         qDebug( "Room Table Validated..." );

     qry.prepare("SELECT price FROM restorders WHERE guestid = :guestID");
     qry.bindValue(":guestid",guestID);
     if(!qry.exec())
         qDebug() << qry.lastError();
     else
         qDebug( "Room Table Validated..." );
     while (qry.next()) {
         int price = qry.value(0).toInt();
         totalPrice+=price;
     }

     qry.prepare("CREATE TABLE IF NOT EXISTS payments ( id INTEGET PRIMARY KEY, time VARCHAR(25), amount INTEGER, guestID INTEGER )");
     if(!qry.exec())
         qDebug() << qry.lastError();
     else
         qDebug( "Room Table Validated..." );

     qry.prepare("SELECT time,amount FROM payments WHERE guestID = :guestID");
     qry.bindValue(":guestid",guestID);
     if(!qry.exec())
         qDebug() << qry.lastError();
     else
         qDebug( "Room Table Validated..." );

     int totalPay = 0;
     while (qry.next()) {
         int price = qry.value(1).toInt();
         totalPay+=price;
         }


     QString TBStr1;
     TBStr1.setNum(totalPrice);
     ui->totalBill->setText(TBStr1);


     QString TBStr2;
     TBStr2.setNum(totalPay);
     ui->payBill->setText(TBStr2);

     int totalBal = totalPrice - totalPay;
     QString TBStr3;
     TBStr3.setNum(totalBal);
     ui->bal->setText(TBStr3);


     ui->totalBill->setText(TBStr1);
     ui->payBill->setText(TBStr2);
     ui->bal->setText(TBStr3);

     if(totalBal==0)
     {
         ui->payButton->setEnabled(0);
         ui->coButton->setEnabled(1);
     }
    else
     {
         ui->payButton->setEnabled(1);
         ui->coButton->setEnabled(0);
     }


}
