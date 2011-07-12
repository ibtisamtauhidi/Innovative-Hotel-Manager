#include "editroom.h"
#include "ui_editroom.h"
#include <QtSql>
#include <QDebug>

editRoom::editRoom(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editRoom)
{
    ui->setupUi(this);
    QRegExp regExp1("[A-Z0-9][0-9 ][0-9]*");
    ui->roomName->setValidator(new QRegExpValidator(regExp1, this));
    ui->catList->addItem(" :: Select One :: ");
    setupview();
}

editRoom::~editRoom()
{
    delete ui;
}

void editRoom::setupview()
{

    QSqlDatabase db = QSqlDatabase::addDatabase( "QSQLITE" );

    db.setDatabaseName( "./innovativedb.db" );

    if( !db.open() )
    {
        qDebug() << db.lastError();
        qFatal( "MAYDAY!!!\n\nSOMETHING IS WRONG WITH YOUR DATABASE." );
    }

    qDebug( "Database Connection Validated..." );

    QSqlQuery qry;
    qry.prepare("CREATE TABLE IF NOT EXISTS roomcat (id INTEGET PRIMARY KEY, item VARCHAR(30), price INTEGER)");
    if(!qry.exec())
        qDebug() << qry.lastError();
    else
        qDebug( "Room Category Table Validated..." );

    int j=0;

    if(!qry.exec("SELECT item FROM roomcat"))
    {
        qDebug() << qry.lastError();
    }
    else
        qDebug( "Processing Room Category Table..." );

    qDebug() <<"Available Categories:";
    while (qry.next()) {
        QString item = qry.value(0).toString();
        ui->catList->addItem(item);
        qDebug() << item;
        j++;
    }
    db.close();

}

void editRoom::on_roomName_textChanged()
{
    ui->addButton->setEnabled(ui->roomName->hasAcceptableInput());
}

void editRoom::on_addButton_clicked()
{

    QString roomno=ui->roomName->text();

    QString nameStr= ui->catList->currentText();

    QSqlDatabase db = QSqlDatabase::addDatabase( "QSQLITE" );
    db.setDatabaseName( "./innovativedb.db" );
    if( !db.open() )
    {
        qDebug() << db.lastError();
        qFatal( "MAYDAY!!!\n\nSOMETHING IS WRONG WITH YOUR DATABASE." );
    }
    qDebug( "Database Connection Validated..." );
    QSqlQuery qry;

    qry.prepare("CREATE TABLE IF NOT EXISTS roomcat (id INTEGET PRIMARY KEY, item VARCHAR(30), price INTEGER)");
    if(!qry.exec())
        qDebug() << qry.lastError();
    else
        qDebug( "Table Created!" );


    qry.prepare("SELECT id FROM roomcat WHERE item = :name");
    qry.bindValue(":name",nameStr);
    if(!qry.exec())
    {
        qDebug() << qry.lastError();
    }
    else
        qDebug( "Table Selected!" );

    int catid=0;
    while (qry.next()) {
        catid = qry.value(0).toInt();
    }
    if(catid==0)
    {
        qFatal("MAYDAY!!! DATABASE ERROR!!!");
    }

    qry.prepare("CREATE TABLE IF NOT EXISTS roomlist (id INTEGET PRIMARY KEY, roomno VARCHAR(5), cat INTEGER, occupied INTEGER)");
    if(!qry.exec())
        qDebug() << qry.lastError();
    else
        qDebug( "Room Table Validated..." );

    if(!qry.exec("SELECT id FROM roomlist"))
    {
        qDebug() << qry.lastError();
    }
    else
        qDebug( "Table Selected!" );

    int roomid=0;
    while (qry.next()) {

        int item = qry.value(0).toInt();
        if(item>roomid)
        {
            roomid=item;
        }
    }
    roomid++;

    qry.prepare("INSERT INTO roomlist (id, roomno, cat, occupied) values (:id, :roomno, :roomcat, :occ)");
    qry.bindValue(":id",roomid);
    qry.bindValue(":roomno",roomno);
    qry.bindValue(":roomcat",catid);
    qry.bindValue(":occ",0);
    if(!qry.exec())
        qDebug() << qry.lastError();
    else
    {
        qDebug( "Inserted to Room Table." );
        ui->roomList->addItem(ui->roomName->text());
        ui->roomName->clear();
    }

}


void editRoom::on_catList_currentIndexChanged()
{
    ui->roomList->clear();
    QString nameStr= ui->catList->currentText();

    if(nameStr==" :: Select One :: ")
    {
        ui->roomList->clear();
        ui->roomName->setEnabled(0);
        return;
    }
    ui->roomName->setEnabled(1);


    QSqlDatabase db = QSqlDatabase::addDatabase( "QSQLITE" );

    db.setDatabaseName( "./innovativedb.db" );

    if( !db.open() )
    {
        qDebug() << db.lastError();
        qFatal( "Failed to connect." );
    }

    qDebug( "Connected!" );

    QSqlQuery qry;
    qry.prepare("CREATE TABLE IF NOT EXISTS roomcat (id INTEGET PRIMARY KEY, item VARCHAR(30), price INTEGER)");
    if(!qry.exec())
        qDebug() << qry.lastError();
    else
        qDebug( "Table Created!" );


    qry.prepare("SELECT id FROM roomcat WHERE item = :name");
    qry.bindValue(":name",nameStr);
    if(!qry.exec())
    {
        qDebug() << qry.lastError();
    }
    else
        qDebug( "Table Selected!" );

    int i=0;
    while (qry.next()) {
        i = qry.value(0).toInt();
    }

    if(i==0)
    {
        qFatal("MAYDAY!!! DATABASE ERROR!!!");
    }

    qry.prepare("CREATE TABLE IF NOT EXISTS roomlist (id INTEGET PRIMARY KEY, roomno VARCHAR(5), cat INTEGER, occupied INTEGER)");
    if(!qry.exec())
        qDebug() << qry.lastError();
    else
        qDebug( "Room Table Validated..." );

    qry.prepare("SELECT roomno FROM roomlist WHERE cat = :item");
    qry.bindValue(":item",i);
    if(!qry.exec())
        qDebug() << qry.lastError();
    else
        qDebug( "Room Table Validated..." );

    while (qry.next()) {
        QString roomno = qry.value(0).toString();
        ui->roomList->addItem(roomno);
    }
}

void editRoom::on_okButton_clicked()
{
    this->close();
}
