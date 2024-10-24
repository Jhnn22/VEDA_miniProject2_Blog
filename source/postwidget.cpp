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

    commentWidget = nullptr;
}

PostWidget::~PostWidget()
{
    delete ui;
}


/*
 * 현재 A->A, A->B는 괜찮은데, A->B->A이런식으로 갔다오면 댓글이 지워짐
 * 게시글 목록이나 댓글 목록이나 서버랑 통신으로 가져와서 토큰, 위젯을 묶어서 맵으로 저장해야 할 것 같다..
 * 죄송합니다/...ㅠㅜ
 */
void PostWidget::setComments(const QString &postId){
    if (!commentWidget || this->currentPostId != postId) {
        if (commentWidget) {
            delete commentWidget;
            commentWidget = nullptr;
        }

        commentWidget = new CommentWidget(this);
        commentWidget->getInfos(token, postId, userId);

        ui->verticalLayout->addWidget(commentWidget);

        this->currentPostId = postId;
    }
}

void PostWidget::setButtons(QWidget *clickedPostWidget){
    QString postId = clickedPostWidget->property("postId").toString();

    if(isButtonConnected){
        disconnect(ui->editPushButton, nullptr, nullptr, nullptr);
        disconnect(ui->deletePushButton, nullptr, nullptr, nullptr);
    }

    connect(ui->exitPushButton, &QPushButton::clicked, this, &PostWidget::exit);
    connect(ui->editPushButton, &QPushButton::clicked, this, [this, postId](){
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
            Network::instance()->postEditAttempt(token, postId, title, content, currentDateTime, userId);
        }
    });
    connect(ui->deletePushButton, &QPushButton::clicked, this, [this, postId](){
        Network::instance()->postDeleteAttempt(token, postId);
    });
    isButtonConnected = true;

    connect(Network::instance(), &Network::postEditSuccess, this, [this](const QString &token, const QString &postId, const QString &title, const QString &content, const QString &currentDateTime){
        ui->editPushButton->setText("편집");
        ui->lineEdit->setReadOnly(isEditing);
        ui->textEdit->setReadOnly(isEditing);
        isEditing = false;

        emit editPostList(token, postId, title, content, currentDateTime);
        emit exit();
    });
    connect(Network::instance(), &Network::postEditFailed, this, [this](){
        // 게시글 편집 실패
    });

    connect(Network::instance(), &Network::postDeleteSuccess, this, [this](const QString &token, const QString &postId){
        emit deletePostList(token, postId);
        emit exit();
    });
    connect(Network::instance(), &Network::postDeleteFailed, this, [this](){
        // 게시글 삭제 실패
    });

}

void PostWidget::openPost_2(QWidget *clickedPostWidget){
    // 위젯의 속성에서 데이터 가져오기
    QString postId = clickedPostWidget->property("postId").toString();
    QString title = clickedPostWidget->property("title").toString();
    QString content = clickedPostWidget->property("content").toString();
    QString currentDateTime = clickedPostWidget->property("currentDateTime").toString();

    // 테스트
    qDebug() << "-------------------------";
    qDebug() << "Post ID:" << postId;
    qDebug() << "Title:" << title;
    qDebug() << "Content:" << content;
    qDebug() << "Date/Time:" << currentDateTime;

    ui->lineEdit->setText(title);
    QString ymd = QDateTime::currentDateTime().toString("yyyy-MM-dd ");
    ui->label->setText(userId + " | 작성일: " + ymd + currentDateTime);
    ui->textEdit->setText(content);

    ui->lineEdit->setReadOnly(true);
    ui->textEdit->setReadOnly(true);
    isEditing = false;

    setButtons(clickedPostWidget);
    setComments(postId);
}

void PostWidget::getInfos(const QString &token, const QString &userId){
    this->token = token;
    this->userId = userId;
}
