#include "editroomcat.h"
#include "ui_editroomcat.h"
#include "editaddroomcat.h"
#include <QDebug>
#include <QtSql>
#include <QListWidgetItem>

editRoomCat::editRoomCat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editRoomCat)
{
    ui->setupUi(this);
    setupView();
}

editRoomCat::~editRoomCat()
{
    delete ui;
}

void editRoomCat::setupView()
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
    qry.prepare("CREATE TABLE IF NOT EXISTS roomcat (id INTEGET PRIMARY KEY, item VARCHAR(30), price INTEGER)");
    if(!qry.exec())
      qDebug() << qry.lastError();
    else
      qDebug( "Table Created!" );

    int j=0;

    if(!qry.exec("SELECT item FROM roomcat"))
    {
        qDebug() << qry.lastError();
    }
    else
        qDebug( "Table Selected!" );

    ui->catList->clear();
    while (qry.next()) {
        QString item = qry.value(0).toString();

        ui->catList->addItem(item);

        qDebug() << item;
        j++;

    }
}

void editRoomCat::on_addCat_clicked()
{
    InnOeARCat = new editAddRoomCat;
    connect(InnOeARCat,SIGNAL(finished(int)),this,SLOT(setupviewagain()));
    InnOeARCat->show();
}

void editRoomCat::on_rmCat_clicked()
{
    int num=ui->catList->currentRow();
    if( num > -1)
    {

        QListWidgetItem * nameItem = ui->catList->item(num);
        QString nameStr = nameItem->text();

        QSqlDatabase db = QSqlDatabase::addDatabase( "QSQLITE" );

        db.setDatabaseName( "./innovativedb.db" );

        if( !db.open() )
        {
            qDebug() << db.lastError();
            qFatal( "Failed to connect." );
        }

        qDebug( "Connected ghjghjg!" );

        QSqlQuery qry;

        qry.prepare("CREATE TABLE IF NOT EXISTS roomcat (id INTEGET PRIMARY KEY, item VARCHAR(30), price INTEGER)");
        if(!qry.exec())
            qDebug() << qry.lastError();
        else
            qDebug( "Table Created!" );

        qDebug() << nameStr;
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

        qry.prepare("DELETE FROM roomlist WHERE cat = :cat");
        qry.bindValue(":cat",i);
        if(!qry.exec())
        {
            qDebug() << qry.lastError();
        }
        else
            qDebug( "rooms deleted!" );


        qry.prepare("DELETE FROM roomcat WHERE item=:name");
        qry.bindValue(":name",nameStr);
        if(!qry.exec())
        {
            qDebug() << qry.lastError();
        }
        else
        {
            setupviewagain();
        }
    }
}

void editRoomCat::on_catList_currentTextChanged()
{
    ui->rmCat->setEnabled(0);
    int num=ui->catList->currentRow();
    if( num > -1)
    {
        QListWidgetItem * categoryItem = ui->catList->item(num);
        QString catStr = categoryItem->text();
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
        qry.bindValue(":name",catStr);
        if(!qry.exec())
          qDebug() << qry.lastError();
        else
          qDebug( "Table Created!" );

        int catID = 0;
        while(qry.next())
        {
            catID = qry.value(0).toInt();
        }

        qry.prepare("SELECT occupied FROM roomlist WHERE cat = :cat");
        qry.bindValue(":cat",catID);
        if(!qry.exec())
          qDebug() << qry.lastError();
        else
          qDebug( "Table Created!" );
        int occupied = 0;
        while(qry.next())
        {
            if(qry.value(0).toInt()!=0)
                occupied = 1;
        }
        if (occupied==0)
            ui->rmCat->setEnabled(1);
        else
            ui->rmCat->setEnabled(0);
    }
}
void editRoomCat::on_okButton_clicked()
{
    this->close();
}
void editRoomCat::setupviewagain()
{
    setupView();
}
