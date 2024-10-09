#include "mainwidget.h"
#include "./ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    // stackedWidget에 검색, 글쓰기 페이지 등록
    searchWidget = new SearchWidget(this);
    writeWidget = new WriteWidget(this);
    ui->stackedWidget->insertWidget(1, searchWidget);
    ui->stackedWidget->insertWidget(2, writeWidget);

    // 버튼 클릭시 해당 페이지로 stackedWidget 전환
    ui->stackedWidget->setCurrentIndex(0);
    connect(ui->search_pushButton, &QPushButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(1);
    });
    connect(ui->write_pushButton, &QPushButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(2);
    });


}

MainWidget::~MainWidget()
{
    delete ui;
}
