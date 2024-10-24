#include "writewidget.h"
#include "ui_writewidget.h"
#include "network.h"
#include <QToolBar>
#include <QDateTime>

WriteWidget::WriteWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WriteWidget)
{
    ui->setupUi(this);

    setInputFields();
    setButtons();
}

WriteWidget::~WriteWidget()
{
    delete ui;
}

void WriteWidget::setInputFields(){
    ui->titleLineEdit->setPlaceholderText("제목을 입력하세요");
    ui->textEdit->setPlaceholderText("내용을 입력하세요");
}

void WriteWidget::clearInputFields(){
    ui->titleLineEdit->clear();
    ui->textEdit->clear();
}

void WriteWidget::setButtons(){
    connect(ui->exitPushButton, &QPushButton::clicked, this, [this](){
        clearInputFields();
        emit exit();
    });

    connect(ui->temporarySavePushButton, &QPushButton::clicked, this, &WriteWidget::exit);

    connect(ui->postRegisterPushButton, &QPushButton::clicked, this, [this](){
        if(!ui->titleLineEdit->text().isEmpty() && !ui->textEdit->toPlainText().isEmpty()){
            QString title = ui->titleLineEdit->text();
            QString content = ui->textEdit->toPlainText();
            QString currentDateTime = QDateTime::currentDateTime().toString("HH:mm");

            Network::instance()->postRegisterAttempt(token, title, content, currentDateTime, userId);
        }
        else{
            // 빈칸 존재
        }
    });
    connect(Network::instance(), &Network::postRegisterSuccess, this, [this](const QString &token, const QString &postId, const QString &title, const QString &content, const QString &currentDateTime){
        emit postRegisterSuccess_2(token, postId, title, content, currentDateTime);

        clearInputFields();
        emit exit();
    });
    connect(Network::instance(), &Network::postRegisterFailed, this, [this](const QString &errorMessage){
        // 게시글 등록 실패
    });
}

void WriteWidget::getInfos(const QString &token, const QString &userId){
    this->token = token;
    this->userId = userId;
}
