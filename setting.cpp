#include "setting.h"
#include "ui_setting.h"
#include <QtSql>
#include <QDebug>

setting::setting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setting)
{
    ui->setupUi(this);
    QRegExp regExp1("[A-Za-z0-9][A-Za-z0-9' ]..*");
    ui->name->setValidator(new QRegExpValidator(regExp1, this));
    QRegExp regExp2("[A-Za-z0-9][A-Za-z0-9 ]....[A-Za-z0-9 ]*");
    ui->motto->setValidator(new QRegExpValidator(regExp2, this));
}
setting::~setting()
{
    delete ui;
}
void setting::on_motto_textChanged()
{
    ui->ok->setEnabled((ui->name->hasAcceptableInput())&&(ui->motto->hasAcceptableInput()));
}
void setting::on_name_textChanged()
{
    ui->ok->setEnabled((ui->name->hasAcceptableInput())&&(ui->motto->hasAcceptableInput()));
}
void setting::on_ok_clicked()
{
    QString name = ui->name->text();
    QString motto = ui->motto->text();

    QSqlDatabase db = QSqlDatabase::addDatabase( "QSQLITE" );

    db.setDatabaseName( "./innovativedb.db" );

    if( !db.open() )
    {
        qDebug() << db.lastError();
        qFatal( "Failed to connect." );
    }

    qDebug( "Connected!" );

    QSqlQuery qry;


    qry.prepare("CREATE TABLE IF NOT EXISTS settings (id INTEGET PRIMARY KEY, key VARCHAR(10), value VARCHAR(40))");
    if(!qry.exec())
      qDebug() << qry.lastError();
    else
      qDebug( "Table Created!" );

    qry.prepare("DELETE FROM settings WHERE key = 'name'");
    if(!qry.exec())
    {
        qDebug() << qry.lastError();
    }

    qry.prepare("DELETE FROM settings WHERE key = 'motto'");
    if(!qry.exec())
    {
        qDebug() << qry.lastError();
    }
    if(!qry.exec("SELECT id FROM settings"))
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

    qry.prepare( "INSERT INTO settings ( id, key, value ) VALUES ( :id, 'name', :value )" );
    qry.bindValue(":id",i);
    qry.bindValue(":value",name);
    if(!qry.exec())
      qDebug() << qry.lastError();
    else
      qDebug( "Name Inserted!" );

    qry.prepare( "INSERT INTO settings ( id, key, value ) VALUES ( :id, 'motto', :value )" );
    qry.bindValue(":id",i+1);
    qry.bindValue(":value",motto);
    if(!qry.exec())
      qDebug() << qry.lastError();
    else
      qDebug( "Name Inserted!" );

    this->close();
}
