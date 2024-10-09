#include "writewidget.h"
#include "ui_writewidget.h"

WriteWidget::WriteWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WriteWidget)
{
    ui->setupUi(this);
}

WriteWidget::~WriteWidget()
{
    delete ui;
}
