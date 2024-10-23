#include "accountdialog.h"
#include "ui_accountdialog.h"
#include "network.h"

AccountDialog::AccountDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AccountDialog)
{
    ui->setupUi(this);

    network = new Network;

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
    ui->pwLineEdit->setEchoMode(QLineEdit::Password);

    ui->idLineEdit_2->setPlaceholderText("아이디");
    ui->pwLineEdit_2->setPlaceholderText("비밀번호");
    ui->pwLineEdit_2->setEchoMode(QLineEdit::Password);
    ui->pwCheckLineEdit->setPlaceholderText("비밀번호 확인");
    ui->pwCheckLineEdit->setEchoMode(QLineEdit::Password);

}

void AccountDialog::clearLoginInputFields(){
    ui->idLineEdit->clear();
    ui->pwLineEdit->clear();
}

void AccountDialog::clearCreateAccountInputFields(){
    ui->idLineEdit_2->clear();
    ui->pwLineEdit_2->clear();
    ui->pwCheckLineEdit->clear();
}

void AccountDialog::setButtons(){
    // 로그인
    connect(ui->loginPushButton, &QPushButton::clicked, this, [this](){
        if(!ui->idLineEdit->text().isEmpty() && !ui->pwLineEdit->text().isEmpty()){
            QString id = ui->idLineEdit->text();
            QString pw = ui->pwLineEdit->text();
            network->loginAttempt(id, pw);
        }
        else{
            // 경고 - 빈칸 존재
        }
    });
    connect(network, &Network::loginSuccess, this, [this](const QString &id){
        clearLoginInputFields();
        emit loginSuccess_2(id);
        accept();
    });
    connect(network, &Network::loginFailed, this, [this](const QString &errorMessage){
        clearLoginInputFields();
        // 경고 - 로그인 실패
    });
    connect(ui->createAccountPushButton, &QPushButton::clicked, this, [this](){
        clearLoginInputFields();
        ui->stackedWidget->setCurrentIndex(1);
    });

    // 회원가입
    connect(ui->createAccountPushButton_2, &QPushButton::clicked, this, [this](){
        if(!ui->idLineEdit_2->text().isEmpty() && !ui->pwLineEdit_2->text().isEmpty() && !ui->pwCheckLineEdit->text().isEmpty()){
            if(ui->pwLineEdit_2->text() == ui->pwCheckLineEdit->text()){
                QString id = ui->idLineEdit_2->text();
                QString pw = ui->pwLineEdit_2->text();
                network->createAccountAttempt(id, pw);
            }
            else{
                // 경고 - 비밀번호 확인 실패
            }
        }
        else{
            // 경고 - 빈칸 존재
        }
    });
    connect(network, &Network::createAccountSuccess, this, [this](){
        clearCreateAccountInputFields();
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(network, &Network::createAccountFailed, this, [this](const QString &errorMessage){
        clearCreateAccountInputFields();
        // 경고 - 회원가입 실패
    });
    connect(ui->exitPushButton, &QPushButton::clicked, this, [this](){
        clearCreateAccountInputFields();
        ui->stackedWidget->setCurrentIndex(0);
    });
}

void AccountDialog::openAccountDialog(){
    ui->stackedWidget->setCurrentIndex(0);
    this->exec();
}
