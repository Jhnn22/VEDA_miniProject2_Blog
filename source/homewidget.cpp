#include "homewidget.h"
#include "ui_homewidget.h"
#include "accountdialog.h"
#include "postlistwidget.h"

HomeWidget::HomeWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::HomeWidget)
{
    ui->setupUi(this);
    ui->infoWidget->setVisible(false);

    postListWidget = new PostListWidget(this);

    isLoggedIn = false;

    setPages();
    setButtons();
}

HomeWidget::~HomeWidget()
{
    delete ui;
}

void HomeWidget::setPages(){
    ui->stackedWidget->addWidget(postListWidget);

    ui->stackedWidget->setCurrentIndex(0);  // 초기화면은 게시글 목록
}

void HomeWidget::setButtons(){
    // 검색
    connect(ui->searchPushButton, &QPushButton::clicked, this, [this](){
        qDebug() << "검색";
    });
    // 글쓰기
    connect(ui->writePushButton, &QPushButton::clicked, this, &HomeWidget::write);
    updateButtons();    // 검색, 글쓰기 버튼 상태 업데이트

    // 내 글 목록
    connect(ui->myPostPushButton, &QPushButton::clicked, this, [=](){
        qDebug() << "내 글 목록";
    });
    // 내 댓글 목록
    connect(ui->myCommentPushButton, &QPushButton::clicked, this, [=](){
        qDebug() << "내 댓글 목록";
    });
    // 로그아웃
    connect(ui->logoutPushButton, &QPushButton::clicked, this, [=](){
        isLoggedIn = false;
        updateButtons();
    });
    // 회원탈퇴
    connect(ui->deleteAccountPushButton, &QPushButton::clicked, this, [=](){
        qDebug() << "회원탈퇴";
    });
}

void HomeWidget::updateButtons(){
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
        connect(accountDialog, &AccountDialog::loginSuccess, this, &HomeWidget::handleLoginResult);
    }
}

void HomeWidget::handleLoginResult(){
    qDebug() << "로그인 성공";
    isLoggedIn = true;
    updateButtons();
}

void HomeWidget::updatePostList(const QString &title, const QString &content){
    postListWidget->setPostList(title, content);
}
