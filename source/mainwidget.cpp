#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "homewidget.h"
#include "writewidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    homeWidget = new HomeWidget(this);
    writeWidget = new WriteWidget(this);

    setPages();
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::setPages(){
    ui->stackedWidget->addWidget(homeWidget);
    ui->stackedWidget->addWidget(writeWidget);
    ui->stackedWidget->setCurrentIndex(0);

    connect(homeWidget, &HomeWidget::openWriteWidget, this, [this](){
        ui->stackedWidget->setCurrentIndex(1);
    });
    connect(homeWidget, &HomeWidget::loginSuccess_3, this, [this](const QString &id){
        memberID = id;
    });

    connect(writeWidget, &WriteWidget::exit, this, [this](){
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(writeWidget, &WriteWidget::postRegisterSuccess, homeWidget, &HomeWidget::updatePostList);
}

