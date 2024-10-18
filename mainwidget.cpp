#include "mainwidget.h"
#include "homewidget.h"
#include "writewidget.h"
#include "./ui_mainwidget.h"
#include <algorithm>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    homeWidget = new HomeWidget(this);
    writeWidget = new WriteWidget(this);

    set_page();
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::set_page(){

    ui->stackedWidget->addWidget(homeWidget);
    ui->stackedWidget->addWidget(writeWidget);

    ui->stackedWidget->setCurrentIndex(0); // 초기화면은 mainWidget
}



