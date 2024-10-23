#include "postwidget.h"
#include "ui_postwidget.h"
#include "commentwidget.h"

PostWidget::PostWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PostWidget)
{
    ui->setupUi(this);

    commentWidget = new CommentWidget(this);

    setComments();
    setButtons();
}

PostWidget::~PostWidget()
{
    delete ui;
}

void PostWidget::setComments(){
    ui->verticalLayout->addWidget(commentWidget);
}

void PostWidget::setButtons(){
    connect(ui->exitPushButton, &QPushButton::clicked, this, &PostWidget::exit);
}

void PostWidget::showPostDetail(const Post &post){
    qDebug() << "---------------------";
    qDebug() << "제목: " + post.title;
    qDebug() << "작성일: " + post.date.toString("MM-dd HH:mm");
    qDebug() << "내용: " + post.content;

    ui->label->setText(post.title);
    ui->label_2->setText("JH | 댓글: 0개 | 작성일: " + post.date.toString("MM-dd HH:mm"));
    ui->textEdit->setText(post.content);
    ui->textEdit->setReadOnly(true);
}
