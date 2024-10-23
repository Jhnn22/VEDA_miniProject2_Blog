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

void CommentDisplayWidget::setInputFields(const QString &comment){
    QDateTime date = QDateTime::currentDateTime();
    ui->commentInfoLabel->setText("JH | " + date.toString("yyyy-MM-dd HH:mm"));
    ui->commentTextEdit->setPlainText(comment);
    ui->commentTextEdit->setReadOnly(true);
}

void CommentDisplayWidget::setButtons(){
    connect(ui->editPushButton, &QPushButton::clicked, this, [this](){
        qDebug() << "편집";
    });
    connect(ui->deletePushButton, &QPushButton::clicked, this, [this](){
        qDebug() << "삭제";
    });
}
