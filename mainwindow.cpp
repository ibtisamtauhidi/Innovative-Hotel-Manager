#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "roomspercat.h"
#include "checkinform.h"
#include "checkoutform.h"
#include "addrestaurantorder.h"
#include "addotherorders.h"
#include "editroomcat.h"
#include "editroom.h"
#include "editrestaurant.h"
#include "billingmanager.h"
#include <QtSql>
#include <QDebug>

mainWindow::mainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainWindow)
{
    ui->setupUi(this);


    setupview();
}

mainWindow::~mainWindow()
{
    delete ui;
}
void mainWindow::on_button1_clicked()
{
    InnOrpc = new roomsPerCat;
    connect(InnOrpc,SIGNAL(finished(int)),this,SLOT(setupviewS()));
    InnOrpc->show();
}
void mainWindow::on_button2_clicked()
{
    InnOcif = new checkInForm;
    connect(InnOcif,SIGNAL(finished(int)),this,SLOT(setupviewS()));
    InnOcif->show();
}
void mainWindow::on_button3_clicked()
{
    InnOcof = new checkOutForm;
    connect(InnOcof,SIGNAL(finished(int)),this,SLOT(setupviewS()));
    InnOcof->show();
}
void mainWindow::on_button4_clicked()
{
    InnOaro=new addRestaurantOrder;
    connect(InnOaro,SIGNAL(finished(int)),this,SLOT(setupviewS()));
    InnOaro->show();
}
void mainWindow::on_button5_clicked()
{
    InnOaoo= new addOtherOrders;
    connect(InnOaoo,SIGNAL(finished(int)),this,SLOT(setupviewS()));
    InnOaoo->show();
}
void mainWindow::on_button6_clicked()
{
    InnOerc=new editRoomCat;
    connect(InnOerc,SIGNAL(finished(int)),this,SLOT(setupviewS()));
    InnOerc->show();
}
void mainWindow::on_button7_clicked()
{
    InnOeroom=new editRoom;
    connect(InnOeroom,SIGNAL(finished(int)),this,SLOT(setupviewS()));
    InnOeroom->show();
}
void mainWindow::on_button8_clicked()
{
    InnOerest=new editRestaurant;
    connect(InnOerest,SIGNAL(finished(int)),this,SLOT(setupviewS()));
    InnOerest->show();
}
void mainWindow::on_button9_clicked()
{
    InnObill= new billingManager;
    connect(InnObill,SIGNAL(finished(int)),this,SLOT(setupviewS()));
    InnObill->show();
}

void mainWindow::setupview()
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

    if(!qry.exec("SELECT occupied FROM roomlist"))
    {
        qDebug() << qry.lastError();
    }
    else
        qDebug( "Table Selected!" );

    int total=0;
    int empty=0;
    while(qry.next()) {
        int temp = qry.value(0).toInt();
        if(temp==0) empty++;
        total++;
    }
    int occupied = total - empty;

    ui->totalL->setNum(total);
    ui->emptyL->setNum(empty);
    ui->occupiedL->setNum(occupied);

}
void mainWindow::setupviewS()
{
    setupview();
}
