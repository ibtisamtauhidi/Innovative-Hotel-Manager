#include "addotherorders.h"
#include "ui_addotherorders.h"
#include <QtSql>
#include <QDebug>
#include <QDateTime>

addOtherOrders::addOtherOrders(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addOtherOrders)
{
    ui->setupUi(this);

    QRegExp regExp1("[A-Za-z0-9][A-Za-z0-9 ].[A-Za-z0-9 ]*");
    ui->name->setValidator(new QRegExpValidator(regExp1, this));
    QRegExp regExp2("[1-9][0-9]*");
    ui->price->setValidator(new QRegExpValidator(regExp2, this));

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

addOtherOrders::~addOtherOrders()
{
    delete ui;
}

void addOtherOrders::on_roomNo_currentIndexChanged()
{
    QString roomno = ui->roomNo->currentText();
    qDebug() << roomno;

    if(roomno==":: select one ::")
    {
        ui->okButton->setEnabled(0);
        ui->name->setEnabled(0);
        ui->price->setEnabled(0);
        ui->nameLabel->setText("-");
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
        ui->nameLabel->setText(cur_item);
        ui->name->setEnabled(1);
        ui->price->setEnabled(1);
    }

}


void addOtherOrders::on_okButton_clicked()
{
    QString text = ui->name->text();
    QString price = ui->price->text();
    QString roomno = ui->roomNo->currentText();

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

    qry.prepare("CREATE TABLE IF NOT EXISTS otherorders (id INTEGER PRIMARY KEY, time VARCHAR(30), text VARCHAR(40), price INTEGER, guestid INTEGER)");
    if(!qry.exec())
        qDebug() << qry.lastError();
    else
        qDebug( "Room Table Validated..." );


    int id=0;
    qry.prepare("SELECT id FROM otherorders");
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


    qDebug() << id << text << price << guestID;
    qry.prepare("INSERT INTO otherorders (id,time,text,price,guestid) VALUES (:id,:time,:text,:price,:guestid)");
    qry.bindValue(":id",id);
    qry.bindValue(":time",QDTStr);
    qry.bindValue(":text",text);
    qry.bindValue(":price",price);
    qry.bindValue(":guestid",guestID);
    if(!qry.exec())
        qDebug() << qry.lastError();
    else
        qDebug( "Room Table Validated..." );


    this->close();
}

void addOtherOrders::on_name_textChanged()
{
    ui->okButton->setEnabled((ui->name->hasAcceptableInput())&&(ui->price->hasAcceptableInput()));
}

void addOtherOrders::on_price_textChanged()
{
    ui->okButton->setEnabled((ui->name->hasAcceptableInput())&&(ui->price->hasAcceptableInput()));
}
