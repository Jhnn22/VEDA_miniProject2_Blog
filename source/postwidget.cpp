#include "postwidget.h"
#include "ui_postwidget.h"
#include "commentwidget.h"
#include "network.h"
#include <QDateTime>
#include <QJsonArray>
#include <QJsonObject>

PostWidget::PostWidget(QWidget *parent)
    : QWidget(parent), isButtonConnected(false)
    , ui(new Ui::PostWidget)
{
    ui->setupUi(this);

    commentWidget = nullptr;
}

PostWidget::~PostWidget()
{
    cleanupNetworkConnections();
    clearCurrentComment();

    delete ui;
}


/*
 * 현재 A->A, A->B는 괜찮은데, A->B->A이런식으로 갔다오면 댓글이 지워짐
 * 게시글 목록이나 댓글 목록이나 서버랑 통신으로 가져와서 토큰, 위젯을 묶어서 맵으로 저장해야 할 것 같다..
 * 죄송합니다/...ㅠㅜ
 */
void PostWidget::setComments(const QString &postId){
    clearCurrentComment();
    this->currentPostId = postId;
    loadComments(postId);
}

void PostWidget::loadComments(const QString &postId) {
    // 새 댓글 위젯 생성 및 설정
    commentWidget = new CommentWidget(this);
    commentWidget->getInfos(token, postId, userId);
    ui->verticalLayout->addWidget(commentWidget);

    // 네트워크 시그널 연결
    cleanupNetworkConnections();  // 이전 연결 해제
    connect(Network::instance(), &Network::commentListReceived,
            this, &PostWidget::handleCommentListReceived);
    connect(Network::instance(), &Network::commentListFailed,
            this, &PostWidget::handleCommentListError);

    // 댓글 목록 요청
    Network::instance()->requestCommentList(token, postId);
}

void PostWidget::clearCurrentComment() {
    cleanupNetworkConnections();

    if (commentWidget) {
        commentWidget->disconnect();
        ui->verticalLayout->removeWidget(commentWidget);
        commentWidget->deleteLater();
        commentWidget = nullptr;
    }
}

void PostWidget::handleCommentListReceived(const QString &postId, const QJsonArray &comments) {
    // 현재 표시 중인 게시글의 댓글이 아니면 무시
    if (postId != currentPostId) {
        return;
    }

    // 댓글 위젯에 댓글 목록 전달
    if (commentWidget) {
        commentWidget->clearComments();

        for (const QJsonValue &commentVal : comments) {
            QJsonObject comment = commentVal.toObject();
            QString commentId =  comment["id"].toString();
            QString content = comment["content"].toString();
            QString author = comment["author"].toString();
            QString time = comment["update_time"].toString();

            commentWidget->addComment(commentId, content, author, time);
        }
    }

    // 시그널 연결 해제
    disconnect(Network::instance(), &Network::commentListReceived,
               this, &PostWidget::handleCommentListReceived);
    disconnect(Network::instance(), &Network::commentListFailed,
               this, &PostWidget::handleCommentListError);
}

void PostWidget::handleCommentListError(const QString &error) {
    qDebug() << "댓글 목록 로드 실패:" << error;

    // 시그널 연결 해제
    disconnect(Network::instance(), &Network::commentListReceived,
               this, &PostWidget::handleCommentListReceived);
    disconnect(Network::instance(), &Network::commentListFailed,
               this, &PostWidget::handleCommentListError);
}

void PostWidget::setButtons(QWidget *clickedPostWidget){
    QString postId = clickedPostWidget->property("postId").toString();
    qDebug() << postId;

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
            Network::instance()->postEditAttempt(token, postId, title, content, userId);
        }
    });
    connect(ui->deletePushButton, &QPushButton::clicked, this, [this, postId](){
        Network::instance()->postDeleteAttempt(token, postId);
        qDebug() << postId;
    });
    isButtonConnected = true;

    connect(Network::instance(), &Network::postEditSuccess, this, [this](const QString &token, const QString &postId, const QString &title, const QString &content){
        ui->editPushButton->setText("편집");
        ui->lineEdit->setReadOnly(isEditing);
        ui->textEdit->setReadOnly(isEditing);
        isEditing = false;

        emit editPostList(token, postId, title, content);
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
    qDebug() << postId;
    QString title = clickedPostWidget->property("title").toString();
    QString content = clickedPostWidget->property("content").toString();
    QString currentDateTime = clickedPostWidget->property("currentDateTime").toString();
    QString authorId = clickedPostWidget->property("authorId").toString();

    // 테스트
    qDebug() << "-------------------------";
    qDebug() << "Post ID:" << postId;
    qDebug() << "Title:" << title;
    qDebug() << "Content:" << content;
    qDebug() << "Date/Time:" << currentDateTime;

    ui->lineEdit->setText(title);
    ui->label->setText(authorId + " | 작성일: " + currentDateTime);
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

void PostWidget::cleanupNetworkConnections()
{
    // 네트워크 시그널 연결 해제
    disconnect(Network::instance(), &Network::commentListReceived,
               this, &PostWidget::handleCommentListReceived);
    disconnect(Network::instance(), &Network::commentListFailed,
               this, &PostWidget::handleCommentListError);
}
