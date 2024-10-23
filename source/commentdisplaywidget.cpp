#include "commentdisplaywidget.h"
#include "ui_commentdisplaywidget.h"
#include <QDateTime>

CommentDisplayWidget::CommentDisplayWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CommentDisplayWidget)
{
    ui->setupUi(this);

    setButtons();

}

CommentDisplayWidget::~CommentDisplayWidget()
{
    delete ui;
}

void CommentDisplayWidget::setInputFields(const QString &commentId, const QString &userId, const QString &comment){
    QString currentDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm");
    ui->commentInfoLabel->setText(userId + " | " + currentDateTime);
    ui->commentTextEdit->setPlainText(comment);
    ui->commentTextEdit->setReadOnly(true);
}

void CommentDisplayWidget::setButtons(){
    connect(ui->editPushButton, &QPushButton::clicked, this, [this](){

    });
    connect(ui->deletePushButton, &QPushButton::clicked, this, [this](){
        qDebug() << "삭제";
    });
}

void CommentDisplayWidget::getUserId(const QString &userId){
    this->userId = userId;
}
