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

void CommentWidget::getInfos(const QString &token, const QString &postId, const QString &userId){
    this->token = token;
    this->postId = postId;
    this->userId = userId;
}
