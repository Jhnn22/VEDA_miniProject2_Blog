#include "writewidget.h"
#include "ui_writewidget.h"
#include <QToolBar>

WriteWidget::WriteWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WriteWidget)
{
    ui->setupUi(this);

    setInputFields();
    setButtons();
    setToolButtons();
}

WriteWidget::~WriteWidget()
{
    delete ui;
}

void WriteWidget::setInputFields(){
    ui->titleLineEdit->setPlaceholderText("제목을 입력하세요");
    ui->textEdit->setPlaceholderText("내용을 입력하세요");
}

void WriteWidget::setButtons(){
    connect(ui->exitPushButton, &QPushButton::clicked, this, &WriteWidget::exit);
    connect(ui->temporarySavePushButton, &QPushButton::clicked, this, [=](){
        qDebug() << "임시 저장";
    });
    connect(ui->postRegisterPushButton, &QPushButton::clicked, this, [this](){
        QString title = ui->titleLineEdit->text();
        QString content = ui->textEdit->toPlainText();

        emit postRegisterAttempt(title, content); // 네트워크 클래스로 데이터 전송
        emit postRegisterSuccess(title, content); // 테스트 코드
    });
}

void WriteWidget::setToolButtons(){
    QToolBar *toolBar = new QToolBar(this);
    toolBar->setStyleSheet("QToolBar { background: white; }");

    ui->horizontalLayout->addWidget(toolBar);
}
