#include "billingmanager.h"
#include "ui_billingmanager.h"
#include <QtSql>
#include <QDebug>

billingManager::billingManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::billingManager)
{
    ui->setupUi(this);

    QRegExp regExp("[1-9][0-9]*");
    ui->payForm->setValidator(new QRegExpValidator(regExp, this));

    setupview();
}

billingManager::~billingManager()
{
    delete ui;
}
void billingManager::on_okButton_clicked()
{
    this->close();
}
void billingManager::on_roomNo_currentIndexChanged()
{
    updatetable();
}

void billingManager::setupview()
{
    ui->orders->clear();
    ui->payTab->clear();
    ui->roomNo->clear();
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
    qry.prepare("CREATE TABLE IF NOT EXISTS roomlist ( id INTEGET PRIMARY KEY, roomno VARCHAR(5), cat INTEGER, occupied INTEGER )");
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
void billingManager::updatetable()
{

    ui->orders->clear();
    ui->totalBill->setText("0   ");
    ui->orders->setRowCount(0);
    ui->payForm->setEnabled(1);
    ui->payForm->clear();

    QTableWidgetItem * h1 = new QTableWidgetItem("Item");
    QTableWidgetItem * h2 = new QTableWidgetItem("Date");
    QTableWidgetItem * h3 = new QTableWidgetItem("Price");

    ui->orders->setColumnCount(3);
    ui->orders->setHorizontalHeaderItem(0,h1);
    ui->orders->setHorizontalHeaderItem(1,h2);
    ui->orders->setHorizontalHeaderItem(2,h3);


    QTableWidgetItem * h4 = new QTableWidgetItem("Date");
    QTableWidgetItem * h5 = new QTableWidgetItem("Price");

    ui->payTab->setColumnCount(2);
    ui->payTab->setHorizontalHeaderItem(0,h4);
    ui->payTab->setHorizontalHeaderItem(1,h5);

    QString roomno = ui->roomNo->currentText();
    qDebug() << roomno;

    if(roomno==":: select one ::")
    {
        ui->name->setText("-");
        ui->payForm->setEnabled(0);
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
        ui->name->setText(cur_item);
    }

    qry.prepare("CREATE TABLE IF NOT EXISTS otherorders (id INTEGER PRIMARY KEY, time VARCHAR(30), text VARCHAR(40), price INTEGER, guestid INTEGER)");
    if(!qry.exec())
        qDebug() << qry.lastError();
    else
        qDebug( "Room Table Validated..." );


    qry.prepare("SELECT time,text,price FROM otherorders WHERE guestid = :guestID");
    qry.bindValue(":guestid",guestID);
    if(!qry.exec())
        qDebug() << qry.lastError();
    else
        qDebug( "Room Table Validated..." );
    int totalPrice = 0;
    int r = 0;
    while (qry.next()) {
        QString time = qry.value(0).toString();
        QString text = qry.value(1).toString();
        int price = qry.value(2).toInt();
        totalPrice+=price;

        QString priceStr;
        priceStr.setNum(price);

        QTableWidgetItem * textItem = new QTableWidgetItem(text);
        QTableWidgetItem * priceItem = new QTableWidgetItem(priceStr);
        QTableWidgetItem * timeItem = new QTableWidgetItem(time);

        ui->orders->setRowCount(r+1);
        ui->orders->setItem(r,0,textItem);
        ui->orders->setItem(r,1,timeItem);
        ui->orders->setItem(r,2,priceItem);
        r=r+1;
    }

    qry.prepare("CREATE TABLE IF NOT EXISTS restorders (id INTEGET PRIMARY KEY, item VARCHAR(20), quantity INTEGER, price INTEGER, guestID INTEGER, time VARCHAR(20))");
    if(!qry.exec())
        qDebug() << qry.lastError();
    else
        qDebug( "Room Table Validated..." );

    qry.prepare("SELECT time,item,price FROM restorders WHERE guestid = :guestID");
    qry.bindValue(":guestid",guestID);
    if(!qry.exec())
        qDebug() << qry.lastError();
    else
        qDebug( "Room Table Validated..." );
    while (qry.next()) {
        QString time = qry.value(0).toString();
        QString text = qry.value(1).toString();
        int price = qry.value(2).toInt();
        qDebug() << time << text << price;
        totalPrice+=price;

        QString priceStr;
        priceStr.setNum(price);

        QTableWidgetItem * textItem = new QTableWidgetItem(text);
        QTableWidgetItem * priceItem = new QTableWidgetItem(priceStr);
        QTableWidgetItem * timeItem = new QTableWidgetItem(time);

        ui->orders->setRowCount(r+1);
        ui->orders->setItem(r,0,textItem);
        ui->orders->setItem(r,1,timeItem);
        ui->orders->setItem(r,2,priceItem);
        r=r+1;
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
    r = 0;
    while (qry.next()) {
        QString time = qry.value(0).toString();
        int price = qry.value(1).toInt();
        totalPay+=price;

        qDebug() << time << price;
        QString priceStr;
        priceStr.setNum(price);

        QTableWidgetItem * priceItem = new QTableWidgetItem(priceStr);
        QTableWidgetItem * timeItem = new QTableWidgetItem(time);

        ui->payTab->setRowCount(r+1);
        ui->payTab->setItem(r,0,timeItem);
        ui->payTab->setItem(r,1,priceItem);

        r=r+1;
    }


    QString TBStr1;
    TBStr1.setNum(totalPrice);
    ui->totalBill->setText(TBStr1);


    QString TBStr2;
    TBStr2.setNum(totalPay);
    ui->totalPay->setText(TBStr2);

    int totalBal = totalPrice - totalPay;
    QString TBStr3;
    TBStr3.setNum(totalBal);
    ui->totalBal->setText(TBStr3);

}

void billingManager::on_payButton_clicked()
{

    QString roomno = ui->roomNo->currentText();
    qDebug() << roomno;

    if(roomno==":: select one ::")
    {
        ui->name->setText("-");
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
    QString amount = ui->payForm->text();
    ui->payForm->clear();

    qry.prepare("INSERT INTO payments ( id, time, amount, guestID ) VALUES (:id, :time, :amount, :guestid )");
    qry.bindValue(":id",id);
    qry.bindValue(":time",QDTStr);
    qry.bindValue(":amount",amount);
    qry.bindValue(":guestid",guestID);
    if(!qry.exec())
        qDebug() << qry.lastError();
    else
        qDebug( "Room Table Validated..." );

    updatetable();


}
void billingManager::on_payForm_textChanged()
{
    ui->payButton->setEnabled(ui->payForm->hasAcceptableInput());
}
