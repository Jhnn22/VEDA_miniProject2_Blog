#include "postwidget.h"
#include "ui_postwidget.h"
#include "commentwidget.h"
#include "network.h"
#include <QDateTime>

PostWidget::PostWidget(QWidget *parent)
    : QWidget(parent), isButtonConnected(false)
    , ui(new Ui::PostWidget)
{
    ui->setupUi(this);

    commentWidget = new CommentWidget(this);

    setComments();
}

PostWidget::~PostWidget()
{
    delete ui;
}

void PostWidget::setComments(){
    ui->verticalLayout->addWidget(commentWidget);
}

void PostWidget::setButtons(const Post &post){
    if(!isButtonConnected){
        connect(ui->exitPushButton, &QPushButton::clicked, this, &PostWidget::exit);
        connect(ui->editPushButton, &QPushButton::clicked, this, [this, post](){
            if(!isEditing){
                ui->editPushButton->setText("저장");
                ui->lineEdit->setReadOnly(isEditing);
                ui->textEdit->setReadOnly(isEditing);
                isEditing = true;
            }
            else{
                QString title = ui->lineEdit->text();
                QString content = ui->textEdit->toPlainText();
                QString currentDateTime = QDateTime::currentDateTime().toString("HH:mm");
                Network::instance()->postEditAttempt(post.postId, title, content, currentDateTime, userId);
            }
        });
        connect(ui->deletePushButton, &QPushButton::clicked, this, [this, post](){
            Network::instance()->postDeleteAttempt(post.postId);
        });
    }
    isButtonConnected = true;

    connect(Network::instance(), &Network::postEditSuccess, this, [this](const QString &postId, const QString &title, const QString &content, const QString &currentDateTime){
        ui->editPushButton->setText("편집");
        ui->lineEdit->setReadOnly(isEditing);
        ui->textEdit->setReadOnly(isEditing);
        isEditing = false;

        emit editPostList(postId, title, content, currentDateTime);
        emit exit();
    });
    connect(Network::instance(), &Network::postEditFailed, this, [this](){
        // 게시글 편집 실패
    });

    connect(Network::instance(), &Network::postDeleteSuccess, this, [this](const QString &postId){
        emit deletePostList(postId);
        emit exit();
    });
    connect(Network::instance(), &Network::postDeleteFailed, this, [this](){
        // 게시글 삭제 실패
    });

}

void PostWidget::openPost_2(const Post &post){
    qDebug() << "---------------------";
    qDebug() << "제목: " + post.title;
    qDebug() << "작성자: " + userId;
    qDebug() << "작성일: " + post.currentDateTime;
    qDebug() << "내용: " + post.content;

    ui->lineEdit->setText(post.title);
    QString ymd = QDateTime::currentDateTime().toString("yyyy-MM-dd ");
    ui->label->setText(userId + " | 댓글: " + "개 | 작성일: " + ymd + post.currentDateTime);
    ui->textEdit->setText(post.content);

    ui->lineEdit->setReadOnly(true);
    ui->textEdit->setReadOnly(true);
    isEditing = false;

    setButtons(post);
}

void PostWidget::getUserId(const QString &userId){
    this->userId = userId;
    commentWidget->getUserId(userId);
}
