#include "support.h"
#include "ui_support.h"

support::support(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::support)
{
    ui->setupUi(this);
}

support::~support()
{
    delete ui;
}
