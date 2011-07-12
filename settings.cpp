#include "settings.h"
#include "ui_settings.h"

settings::settings(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::settings)
{
    ui->setupUi(this);
}

settings::~settings()
{
    delete ui;
}
