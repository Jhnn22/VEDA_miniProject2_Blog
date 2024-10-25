#include "commentwidget.h"
#include "ui_commentwidget.h"
#include "commentdisplaywidget.h"
#include "network.h"
#include <QTextEdit>
#include <QBoxLayout>
#include <QLabel>
#include <QDateTime>

CommentWidget::CommentWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CommentWidget)
{
    ui->setupUi(this);

    setButtons();
    setupLayout();
}

CommentWidget::~CommentWidget()
{
    delete ui;
}

void CommentWidget::setButtons(){
    connect(ui->registerPushButton, &QPushButton::clicked, this, [this](){
        if(!ui->commentTextEdit->toPlainText().isEmpty()){
            QString comment = ui->commentTextEdit->toPlainText();
            Network::instance()->commentRegisterAttempt(token, postId, userId, comment);
            ui->commentTextEdit->clear();
        }
        else{
            // 빈칸 존재
        }

    });
    connect(Network::instance(), &Network::commentRegisterSuccess, this, [this](const QString &token, const QString &commentId, const QString &comment){
        CommentDisplayWidget *commentDisplayWidget = new CommentDisplayWidget(this);
        commentDisplayWidget->getInfos(token, userId);
        commentDisplayWidget->setInputFields(token, commentId, comment);
        ui->verticalLayout->addWidget(commentDisplayWidget);
    });
    connect(Network::instance(), &Network::commentRegisterFailed, this, [this](){
        // 댓글 등록 실패
    });
}

void CommentWidget::setupLayout()
{
    // commentsLayout 초기화 및 설정
    commentsLayout = new QVBoxLayout();
    commentsLayout->setContentsMargins(0, 0, 0, 0);
    ui->verticalLayout->addLayout(commentsLayout);
    ui->verticalLayout->addStretch();  // 댓글들을 위쪽으로 정렬
}

void CommentWidget::getInfos(const QString &token, const QString &postId, const QString &userId){
    this->token = token;
    this->postId = postId;
    this->userId = userId;
}

void CommentWidget::clearComments() {
    // 기존 댓글 위젯들 제거
    for (QWidget* widget : commentItems.values()) {
        commentsLayout->removeWidget(widget);
        widget->deleteLater();
    }
    commentItems.clear();
}

void CommentWidget::addComment(const QString &commentId, const QString &content, const QString &author, const QString &time){
    QWidget *commentWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(commentWidget);
    layout->setContentsMargins(0, 0, 0, 5);
    layout->setSpacing(0);

    QLabel *infoLabel = new QLabel(author + " | " + time);
    QLabel *contentLabel = new QLabel(content);

    layout->addWidget(infoLabel);
    layout->addWidget(contentLabel);

    layout->setStretchFactor(infoLabel, 2);
    layout->setStretchFactor(contentLabel, 8);

    commentItems[commentId] = commentWidget;
    commentsLayout->addWidget(commentWidget);
}
