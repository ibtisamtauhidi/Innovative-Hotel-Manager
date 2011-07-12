#include "editrestaurant.h"
#include "ui_editrestaurant.h"
#include "editaddrestaurant.h"
#include "editremrestaurant.h"
#include <QtDebug>
#include <QtSql>
#include <QTableWidgetItem>

editRestaurant::editRestaurant(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editRestaurant)
{
    ui->setupUi(this);
    setupview();
}

editRestaurant::~editRestaurant()
{
    delete ui;
}
void editRestaurant::on_addItem_clicked()
{
    InnOeARes = new editAddRestaurant;
    connect(InnOeARes,SIGNAL(finished(int)),this,SLOT(setupviewagain()));
    InnOeARes->show();
}
void editRestaurant::on_removeItem_clicked()
{
    InnOeRRes = new editRemRestaurant;
    connect(InnOeRRes,SIGNAL(finished(int)),this,SLOT(setupviewagain()));
    InnOeRRes->show();
}
void editRestaurant::setupview()
{
    QSqlDatabase db = QSqlDatabase::addDatabase( "QSQLITE" );

    db.setDatabaseName( "./innovativedb.db" );

    if( !db.open() )
    {
        qDebug() << db.lastError();
        qFatal( "Failed to connect." );
    }

    qDebug( "Connected!" );

    QSqlQuery qry;

    qry.prepare("CREATE TABLE IF NOT EXISTS restmenu (item VARCHAR(30),price INTEGER)");
    if(!qry.exec())
      qDebug() << qry.lastError();
    else
      qDebug( "Table Created!" );

    if(!qry.exec("SELECT * FROM restmenu"))
    {
        qDebug() << qry.lastError();
    }
    else
        qDebug( "Table Selected!" );

    int i=0;

    while (qry.next()) {
        i++;
    }
    ui->restTable->setRowCount(i);

    if(i==0)
    {
        ui->removeItem->setEnabled(0);
    }
    int j=0;
    if(!qry.exec("SELECT * FROM restmenu"))
    {
        qDebug() << qry.lastError();
    }
    else
        qDebug( "Table Selected!" );

    while (qry.next()) {
        QString item = qry.value(0).toString();
        QString price = qry.value(1).toString();

        QTableWidgetItem * itemItem = new QTableWidgetItem(item);
        QTableWidgetItem * priceItem = new QTableWidgetItem(price);

        ui->restTable->setItem(j,0,itemItem);
        ui->restTable->setItem(j,1,priceItem);

        qDebug() << item << "\t:\t" << price;
        j++;

    }
}
void editRestaurant::on_okButton_clicked()
{
    this->close();
}
void editRestaurant::setupviewagain()
{
    setupview();
}
