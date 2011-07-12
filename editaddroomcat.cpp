#include "editaddroomcat.h"
#include "ui_editaddroomcat.h"
#include <QtSql>
#include <QDebug>
#include <QDateTime>

editAddRoomCat::editAddRoomCat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editAddRoomCat)
{
    ui->setupUi(this);
    QRegExp regExp1("[A-Za-z0-9][A-Za-z0-9 ].[A-Za-z0-9 ]*");
    ui->name->setValidator(new QRegExpValidator(regExp1, this));
    QRegExp regExp2("[1-9][0-9][0-9]*");
    ui->price->setValidator(new QRegExpValidator(regExp2, this));

}

editAddRoomCat::~editAddRoomCat()
{
    delete ui;
}

void editAddRoomCat::on_name_textChanged()
{
    ui->okButton->setEnabled((ui->name->hasAcceptableInput())&&(ui->price->hasAcceptableInput()));
}

void editAddRoomCat::on_price_textChanged()
{
    ui->okButton->setEnabled((ui->name->hasAcceptableInput())&&(ui->price->hasAcceptableInput()));
}

void editAddRoomCat::on_okButton_clicked()
{
    QString ItemName = ui->name->text();
    QString ItemPrice = ui->price->text();

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

    if(!qry.exec("SELECT id FROM roomcat"))
    {
        qDebug() << qry.lastError();
    }
    else
        qDebug( "Table Selected!" );
    int i=0;
    while (qry.next()) {

        int item = qry.value(0).toInt();
        if(item>i)
        {
            i=item;
        }
    }
    i++;
    qry.prepare( "INSERT INTO roomcat ( id, item, price ) VALUES ( :id, :item, :price )" );
    qry.bindValue(":id",i);
    qry.bindValue(":item",ItemName);
    qry.bindValue(":price",ItemPrice);
    if(!qry.exec())
      qDebug() << qry.lastError();
    else
      qDebug( "Inserted!" );

    this->close();

}
