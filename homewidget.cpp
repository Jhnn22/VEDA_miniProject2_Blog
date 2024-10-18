#include "homewidget.h"
#include "ui_homewidget.h"

HomeWidget::HomeWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::HomeWidget)
{
    ui->setupUi(this);

    makePage();
}

HomeWidget::~HomeWidget()
{
    delete ui;
}

void HomeWidget::makePage(){
    setMenuBar();
}

void HomeWidget::setMenuBar(){
    connect(ui->searchPushButton, &QPushButton::clicked, this, [=](){
        qDebug() << "search";
    });
    connect(ui->writePushButton, &QPushButton::clicked, this, [=](){
        qDebug() << "write";
    });
    connect(ui->loginPushButton, &QPushButton::clicked, this, [=](){
        qDebug() << "login";
    });
}
