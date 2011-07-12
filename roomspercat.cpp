#include "roomspercat.h"
#include "ui_roomspercat.h"
#include <QtSql>
#include <QDebug>
#include <QTableWidget>

roomsPerCat::roomsPerCat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::roomsPerCat)
{
    ui->setupUi(this);


    ui->cat->setColumnCount(4);
    QSqlDatabase db = QSqlDatabase::addDatabase( "QSQLITE" );

    db.setDatabaseName( "./innovativedb.db" );

    if( !db.open() )
    {
        qDebug() << db.lastError();
        qFatal( "Failed to connect." );
    }

    qDebug( "Connected!" );

    QSqlQuery qry;
    QSqlQuery qry2;

    qry.prepare("CREATE TABLE IF NOT EXISTS roomcat (id INTEGET PRIMARY KEY, item VARCHAR(30), price INTEGER)");
    if(!qry.exec())
      qDebug() << qry.lastError();
    else
      qDebug( "Table Created!" );


    if(!qry.exec("SELECT id,item FROM roomcat"))
    {
        qDebug() << qry.lastError();
    }
    else
        qDebug( "Table Selected!" );

    int i=0;

    while (qry.next()) {
        ui->cat->setRowCount(i+1);
        int id = qry.value(0).toInt();
        QString item = qry.value(1).toString();

        qry2.prepare("SELECT occupied FROM roomlist WHERE cat = :id");
        qry2.bindValue(":id",id);
        if(!qry2.exec())
        {
            qDebug() << qry.lastError();
        }
        else
            qDebug( "Table Selected!" );

        int total=0;
        int empty=0;
        while(qry2.next()) {
            int temp = qry2.value(0).toInt();
            if(temp==0) empty++;
            total++;
        }
        int occupied = total - empty;

        qDebug() << total << empty << occupied;

        QString totalStr, emptyStr, occupiedStr;
        totalStr.setNum(total);
        emptyStr.setNum(empty);
        occupiedStr.setNum(occupied);


        QTableWidgetItem * nameItem = new QTableWidgetItem(item);
        QTableWidgetItem * totalItem = new QTableWidgetItem(totalStr);
        QTableWidgetItem * emptyItem = new QTableWidgetItem(emptyStr);
        QTableWidgetItem * occupiedItem = new QTableWidgetItem(occupiedStr);

        ui->cat->setItem(i,0,nameItem);
        ui->cat->setItem(i,1,totalItem);
        ui->cat->setItem(i,2,emptyItem);
        ui->cat->setItem(i,3,occupiedItem);
        i=i+1;

    }

    QTableWidgetItem * nameH = new QTableWidgetItem("Category");
    QTableWidgetItem * totalH = new QTableWidgetItem("Total");
    QTableWidgetItem * emptyH = new QTableWidgetItem("Empty");
    QTableWidgetItem * occupiedH = new QTableWidgetItem("Occupied");
    ui->cat->setHorizontalHeaderItem(0,nameH);
    ui->cat->setHorizontalHeaderItem(1,totalH);
    ui->cat->setHorizontalHeaderItem(2,emptyH);
    ui->cat->setHorizontalHeaderItem(3,occupiedH);
    ui->cat->setSortingEnabled(1);

}

roomsPerCat::~roomsPerCat()
{
    delete ui;
}
void roomsPerCat::on_ok_clicked()
{
    this->close();
}
