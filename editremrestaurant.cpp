#include "editremrestaurant.h"
#include "ui_editremrestaurant.h"
#include <QtSql>
#include <QDebug>

editRemRestaurant::editRemRestaurant(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editRemRestaurant)
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::addDatabase( "QSQLITE" );

    db.setDatabaseName( "./innovativedb.db" );

    if( !db.open() )
    {
        qDebug() << db.lastError();
        qFatal( "Failed to connect." );
    }

    qDebug( "Connected!" );

    QSqlQuery qry;

    if(!qry.exec("SELECT * FROM restmenu"))
    {
        qDebug() << qry.lastError();
    }
    else
        qDebug( "Table Selected!" );

    int j=0;
    while (qry.next()) {
        QString item = qry.value(0).toString();
        ui->menuList->insertItem(j,item);
        qDebug() << item;
        j++;

    }

}

editRemRestaurant::~editRemRestaurant()
{
    delete ui;
}

void editRemRestaurant::on_okButton_clicked()
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
    QString name = ui->menuList->currentText();

    qry.prepare("DELETE FROM restmenu WHERE item=:name");
    qry.bindValue(":name",name);
    if(!qry.exec())
    {
        qDebug() << qry.lastError();
    }
    else
        qDebug() <<"Deleted : " << name;

        this->close();
}
