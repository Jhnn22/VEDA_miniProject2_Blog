#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "homewidget.h"
#include "writewidget.h"
#include <qlineedit.h>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    homeWidget = new HomeWidget(this);
    writeWidget = new WriteWidget(this);

    setPages();
    setSignalRelay();
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::setPages(){
    ui->stackedWidget->addWidget(homeWidget);
    ui->stackedWidget->addWidget(writeWidget);
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWidget::setSignalRelay(){
    connect(homeWidget, &HomeWidget::write, this, [this](){
        ui->stackedWidget->setCurrentIndex(1);
    });
    connect(writeWidget, &WriteWidget::exit, this, [this](){
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(writeWidget, &WriteWidget::postRegisterSuccess, homeWidget, &HomeWidget::updatePostList);
}
