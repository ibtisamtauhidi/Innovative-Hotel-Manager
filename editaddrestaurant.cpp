#include "editaddrestaurant.h"
#include "ui_editaddrestaurant.h"
#include <QtSql>
#include <QtDebug>

editAddRestaurant::editAddRestaurant(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editAddRestaurant)
{
    ui->setupUi(this);
    QRegExp regExp1("[A-Za-z0-9][A-Za-z0-9 ].[A-Za-z0-9 ]*");
    ui->name->setValidator(new QRegExpValidator(regExp1, this));
    QRegExp regExp2("[1-9][0-9]*");
    ui->price->setValidator(new QRegExpValidator(regExp2, this));

}

editAddRestaurant::~editAddRestaurant()
{
    delete ui;
}

void editAddRestaurant::on_name_textChanged()
{
    ui->okButton->setEnabled((ui->name->hasAcceptableInput())&&(ui->price->hasAcceptableInput()));
}

void editAddRestaurant::on_price_textChanged()
{
    ui->okButton->setEnabled((ui->name->hasAcceptableInput())&&(ui->price->hasAcceptableInput()));
}

void editAddRestaurant::on_okButton_clicked()
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

    qry.prepare("CREATE TABLE IF NOT EXISTS restmenu (item VARCHAR(30),price INTEGER)");
    if(!qry.exec())
      qDebug() << qry.lastError();
    else
      qDebug( "Table Created!" );

    qry.prepare( "INSERT INTO restmenu (item, price) VALUES ( :item, :price )" );
    qry.bindValue(":item",ItemName);
    qry.bindValue(":price",ItemPrice);
    if(!qry.exec())
      qDebug() << qry.lastError();
    else
      qDebug( "Inserted!" );

    this->close();

}
