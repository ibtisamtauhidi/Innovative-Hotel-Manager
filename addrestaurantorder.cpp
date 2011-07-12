#include "addrestaurantorder.h"
#include "ui_addrestaurantorder.h"
#include <QtSql>
#include <QDebug>
#include <QDateTime>
#include <QString>

addRestaurantOrder::addRestaurantOrder(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addRestaurantOrder)
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

    ui->item->addItem(":: select one ::");

    qry.prepare("CREATE TABLE IF NOT EXISTS restmenu (item VARCHAR(30),price INTEGER)");
    if(!qry.exec())
      qDebug() << qry.lastError();
    else
      qDebug( "Table Created!" );


    if(!qry.exec("SELECT item FROM restmenu"))
    {
        qDebug() << qry.lastError();
    }
    else
        qDebug( "Table Selected!" );

    while (qry.next()) {
        QString item = qry.value(0).toString();

        ui->item->addItem(item);
        qDebug() << item;

    }

}


addRestaurantOrder::~addRestaurantOrder()
{
    delete ui;
}


void addRestaurantOrder::on_roomNo_currentIndexChanged()
{

    ui->orderTable->clear();
    ui->orderTable->setRowCount(0);

    QTableWidgetItem * h1 = new QTableWidgetItem("Item");
    QTableWidgetItem * h2 = new QTableWidgetItem("Price");

    ui->orderTable->setHorizontalHeaderItem(0,h1);
    ui->orderTable->setHorizontalHeaderItem(1,h2);

    QString roomno = ui->roomNo->currentText();
    qDebug() << roomno;

    if(roomno==":: select one ::")
    {
        ui->item->setEnabled(0);
        ui->quantityBox->setEnabled(0);
        ui->quantitySlider->setEnabled(0);
        ui->addButton->setEnabled(0);
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
        ui->item->setEnabled(1);
        ui->quantityBox->setEnabled(1);
        ui->quantitySlider->setEnabled(1);
        ui->addButton->setEnabled(0);
    }

    QString item = ui->item->currentText();
    qDebug() << item;

    if(item==":: select one ::")
    {
        ui->quantityBox->setEnabled(0);
        ui->quantitySlider->setEnabled(0);
        ui->addButton->setEnabled(0);
    }

}

void addRestaurantOrder::on_item_currentIndexChanged()
{
    QString item = ui->item->currentText();
    qDebug() << item;

    if(item==":: select one ::")
    {
        ui->quantityBox->setEnabled(0);
        ui->quantitySlider->setEnabled(0);
        ui->addButton->setEnabled(0);
        return;
    }
    ui->quantityBox->setEnabled(1);
    ui->quantitySlider->setEnabled(1);
    ui->addButton->setEnabled(1);
}

void addRestaurantOrder::on_addButton_clicked()
{

   QString item = ui->item->currentText();
   int quantity = ui->quantityBox->value();
   QString roomno = ui->roomNo->currentText();
   qDebug()<<item<<quantity<<roomno;

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

   qry.prepare("SELECT price FROM restmenu WHERE item=:item");
   qry.bindValue(":item",item);
   if(!qry.exec())
       qDebug() << qry.lastError();
   else
       qDebug( "Room Table Validated..." );

   int price = 0;
   while(qry.next())
   {
       price = qry.value(0).toInt();
   }
   price*=quantity;


   qry.prepare("CREATE TABLE IF NOT EXISTS guestlist ( id INTEGET PRIMARY KEY, name VARCHAR(30),address VARCHAR(30), nationality VARCHAR(15), phone VARCHAR(15), occupation VARCHAR(15),purpose VARCHAR(20), occupant INTEGER, room VARCHAR(8), intime VARCHAR(30), outtime VARCHAR(30) )");
   if(!qry.exec())
       qDebug() << qry.lastError();
   else
       qDebug( "Table Created!" );

   qry.prepare("CREATE TABLE IF NOT EXISTS restorders (id INTEGET PRIMARY KEY, item VARCHAR(20), quantity INTEGER, price INTEGER, guestID INTEGER, time VARCHAR(20))");
   if(!qry.exec())
       qDebug() << qry.lastError();
   else
       qDebug( "Room Table Validated..." );


   int id=0;
   qry.prepare("SELECT id FROM restorders");
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

   qry.prepare("INSERT INTO restorders (id,item,quantity,price,guestID,time) VALUES (:id,:item,:quantity,:price,:guestID,:time)");
   qry.bindValue(":id",id);
   qry.bindValue(":item",item);
   qry.bindValue(":quantity",quantity);
   qry.bindValue(":price",price);
   qry.bindValue(":guestID",guestID);
   qry.bindValue(":time",QDTStr);

   if(!qry.exec())
       qDebug() << qry.lastError();
   else
       qDebug( "done..." );

   QString totPrice = ui->total->text();
   int totalprice = totPrice.toInt();
   totalprice+=price;

   QString totalStr;
   totalStr.setNum(totalprice);
   ui->total->setText(totalStr);
    qDebug()<< totalprice;

    QString priceStr;
    priceStr.setNum(price);


   int i = ui->orderTable->rowCount();
   int j=i+1;

   QTableWidgetItem * itemItem = new QTableWidgetItem(item);
   QTableWidgetItem * priceItem = new QTableWidgetItem(priceStr);

   ui->orderTable->setRowCount(j);
   ui->orderTable->setItem(i,0,itemItem);
   ui->orderTable->setItem(i,1,priceItem);


}



void addRestaurantOrder::on_okButton_clicked()
{
    this->close();
}
