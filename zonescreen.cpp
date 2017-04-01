#include "zonescreen.h"
#include "ui_zonescreen.h"

ZoneScreen::ZoneScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZoneScreen)
{
    ui->setupUi(this);
}

ZoneScreen::~ZoneScreen()
{
    delete ui;
}
