#include "accountdialog.h"
#include "ui_accountdialog.h"

AccountDialog::AccountDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AccountDialog)
{
    ui->setupUi(this);

    setInputFields();
    setButtons();
}

AccountDialog::~AccountDialog()
{
    delete ui;
}

void AccountDialog::setInputFields(){
    ui->idLineEdit->setPlaceholderText("아이디");
    ui->pwLineEdit->setPlaceholderText("비밀번호");
}

void AccountDialog::setButtons(){
    // 로그인
    connect(ui->loginPushButton, &QPushButton::clicked, this, [=](){
        emit loginAttempt();                // 네트워크 클래스로 데이터 전송
        emit loginSuccess();     // 테스트 코드
        accept();
    });
    connect(ui->createAccountPushButton, &QPushButton::clicked, this, [this](){
        ui->stackedWidget->setCurrentIndex(1);
    });
    // 회원가입
    connect(ui->exitPushButton, &QPushButton::clicked, this, [this](){
        ui->stackedWidget->setCurrentIndex(0);
    });
}

void AccountDialog::openAccountDialog(){
    ui->stackedWidget->setCurrentIndex(0);
    this->exec();
}
