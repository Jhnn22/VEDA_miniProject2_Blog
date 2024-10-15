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
    connect(ui->searchPushButton, &QPushButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(1);
        qDebug() << "검색 페이지";
    });
    connect(ui->writePushButton, &QPushButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(2);
        qDebug() << "글쓰기 페이지";
    });

    // 버튼 클릭시 infoWidget 토글
    ui->infoWidget->hide();
    connect(ui->infoPushButton, &QPushButton::clicked, this, [=](){
        if(ui->infoWidget->isVisible()) ui->infoWidget->hide();
        else if(ui->infoWidget->isHidden()) ui->infoWidget->show();
    });

    // infoWidget 설정
    connect(ui->myPostListPushButton, &QPushButton::clicked, this, [=](){
        qDebug() << "내 글 목록";
    });
    connect(ui->myCommentsListPushButton, &QPushButton::clicked, this, [=](){
        qDebug() << "내 댓글 목록";
    });
    connect(ui->loginPushButton, &QPushButton::clicked, this, [=](){
        qDebug() << "로그인";
    });
    connect(ui->withdrawMembershipPushButton, &QPushButton::clicked, this, [=](){
        qDebug() << "회원 탈퇴";
    });
}

MainWidget::~MainWidget()
{
    delete ui;
}

