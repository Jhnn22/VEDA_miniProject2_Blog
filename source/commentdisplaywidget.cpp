#include "commentdisplaywidget.h"
#include "ui_commentdisplaywidget.h"
#include <QDateTime>

CommentDisplayWidget::CommentDisplayWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CommentDisplayWidget)
{
    ui->setupUi(this);
}

CommentDisplayWidget::~CommentDisplayWidget()
{
    delete ui;
}

void CommentDisplayWidget::setInputFields(const QString &token, const QString &commentId, const QString &comment){
    QString currentDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm");
    ui->commentInfoLabel->setText(userId + " | " + currentDateTime);
    ui->commentTextEdit->setPlainText(comment);
    ui->commentTextEdit->setReadOnly(true);
}

void CommentDisplayWidget::getInfos(const QString &token, const QString &userId){
    this->token = token;
    this->userId = userId;
}
