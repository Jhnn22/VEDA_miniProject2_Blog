#include "commentwidget.h"
#include "ui_commentwidget.h"
#include "commentdisplaywidget.h"
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

    connect(this, &CommentWidget::commentRegisterSuccess, this, [this](const QString &comment){
        CommentDisplayWidget *commentDisplayWidget = new CommentDisplayWidget(this);
        commentDisplayWidget->setInputFields(comment);
        ui->verticalLayout->addWidget(commentDisplayWidget);
    });
}

CommentWidget::~CommentWidget()
{
    delete ui;
}

void CommentWidget::setButtons(){
    connect(ui->registerPushButton, &QPushButton::clicked, this, [this](){
        QString myComment = ui->myCommentTextEdit->toPlainText();
        emit commentRegisterAttempt(myComment);
        emit commentRegisterSuccess(myComment);
        ui->myCommentTextEdit->clear();
    });
}

