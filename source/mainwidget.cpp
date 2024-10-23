#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "writewidget.h"
#include "accountdialog.h"
#include "postlistwidget.h"
#include "postwidget.h"
#include "post.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    ui->infoWidget->setVisible(false);

    writeWidget = new WriteWidget(this);
    postListWidget = new PostListWidget(this);
    postWidget = new PostWidget(this);

    isLoggedIn = false;

    setPages();
    setButtons();
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::setPages(){
    // writeWidget
    ui->stackedWidget->addWidget(writeWidget);
    ui->stackedWidget->setCurrentIndex(0);

    connect(writeWidget, &WriteWidget::exit, this, [this](){
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(writeWidget, &WriteWidget::postRegisterSuccess_2, postListWidget, &PostListWidget::updatePostList);

    // postListWidget
    ui->stackedWidget_2->addWidget(postListWidget);
    ui->stackedWidget_2->addWidget(postWidget);
    ui->stackedWidget_2->setCurrentIndex(0);

    connect(postListWidget, &PostListWidget::openPost, this, [this](const Post &post){
        postWidget->openPost_2(post);
        ui->stackedWidget_2->setCurrentIndex(1);
    });
    connect(postWidget, &PostWidget::exit, this, [this](){
        ui->stackedWidget_2->setCurrentIndex(0);
    });
    connect(postWidget, &PostWidget::editPostList, postListWidget, &PostListWidget::updatePostList);
    // connect(postWidget, &PostWidget::deletePostList, postListWidget, &PostListWidget::removePostFromList);
}

void MainWidget::setButtons(){
    connect(ui->searchPushButton, &QPushButton::clicked, this, [this](){
        qDebug() << "검색";
    });
    connect(ui->writePushButton, &QPushButton::clicked, this, [this](){
        ui->stackedWidget->setCurrentIndex(1);
    });
    updateButtons();    // 검색, 글쓰기 버튼 상태 업데이트

    connect(ui->myPostPushButton, &QPushButton::clicked, this, [=](){
        qDebug() << "내 글 목록";
    });
    connect(ui->myCommentPushButton, &QPushButton::clicked, this, [=](){
        qDebug() << "내 댓글 목록";
    });
    connect(ui->logoutPushButton, &QPushButton::clicked, this, [=](){
        isLoggedIn = false;
        updateButtons();
    });
    connect(ui->deleteAccountPushButton, &QPushButton::clicked, this, [=](){
        qDebug() << "회원탈퇴";
    });
}

void MainWidget::updateButtons(){
    // 글쓰기 버튼
    ui->writePushButton->setEnabled(isLoggedIn);

    // 로그인 버튼
    disconnect(ui->loginPushButton, nullptr, nullptr, nullptr);
    if(isLoggedIn){
        // 로그인 창 삭제
        accountDialog->deleteLater();
        accountDialog = nullptr;
        // 로그인 버튼 기능 -> 정보 위젯 토글
        ui->loginPushButton->setText("정보");
        connect(ui->loginPushButton, &QPushButton::clicked, this, [this](){
            ui->infoWidget->setVisible(!ui->infoWidget->isVisible());
        });
    }
    else{
        // 드롭 다운 메뉴 숨기기
        ui->infoWidget->setVisible(isLoggedIn);
        // 새로운 로그인 창 생성
        accountDialog = new AccountDialog(this);
        // 로그인 버튼 기능 -> 로그인 창 열기
        ui->loginPushButton->setText("로그인");
        connect(ui->loginPushButton, &QPushButton::clicked, accountDialog, &AccountDialog::openAccountDialog);
        connect(accountDialog, &AccountDialog::loginSuccess_2, this, [this](const QString &id){
            isLoggedIn = true;
            userId = id;
            writeWidget->getUserId(userId);
            postListWidget->getUserId(userId);
            postWidget->getUserId(userId);
            updateButtons();

        });
    }
}
