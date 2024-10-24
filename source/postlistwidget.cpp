#include "postlistwidget.h"
#include "ui_postlistwidget.h"
#include <QHBoxLayout>
#define POSTS_PER_PAGE 9

PostListWidget::PostListWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PostListWidget)
{
    ui->setupUi(this);

    makePage();
    setButtons();
}

PostListWidget::~PostListWidget()
{
    delete ui;
}

void PostListWidget::makePage(){
    QWidget *page = new QWidget(this);

    QVBoxLayout *pageLayout = new QVBoxLayout(page);
    pageLayout->setContentsMargins(0, 0, 0, 0);

    QFrame *frame = new QFrame(page);
    frame->setFrameStyle(QFrame::NoFrame);
    pageLayout->addWidget(frame);

    verticalLayout = new QVBoxLayout(frame);
    verticalLayout->setContentsMargins(0, 0, 0, 0);
    verticalLayout->setSpacing(0);
    verticalLayout->setAlignment(Qt::AlignTop);

    ui->stackedWidget->addWidget(page);
}

void PostListWidget::setButtons(){
    connect(ui->previousPushButton, &QPushButton::clicked, this, [this](){
        if(ui->stackedWidget->currentIndex() > 0){
            ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() - 1);
        }
    });
    connect(ui->nextPushButton, &QPushButton::clicked, this, [this](){
        if(ui->stackedWidget->currentIndex() < ui->stackedWidget->count() - 1){
            ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() + 1);
        }
    });
}

void PostListWidget::updatePostList(const QString &postId, const QString &title, const QString &content, const QString &currentDateTime){
    QWidget *postWidget;

    if(postWidgets.contains(postId)){
        postWidget = postWidgets[postId];

        QList<QLabel*> labels = postWidget->findChildren<QLabel*>();
        if (labels.size() >= 3) {
            labels[0]->setText(title);
            labels[1]->setText(userId);
            labels[2]->setText(currentDateTime);
        }

        postWidget->setProperty("title", title);
        postWidget->setProperty("userId", userId);
        postWidget->setProperty("content", content);
        postWidget->setProperty("currentDateTime", currentDateTime);

        return;
    }

    // 새 페이지 생성
    totalPosts = postWidgets.size();
    if(totalPosts % POSTS_PER_PAGE == 1 && totalPosts > POSTS_PER_PAGE){
        makePage();
    }

    postWidget = new QWidget();
    postWidget->setStyleSheet(
        "QWidget { "
        "    background-color: #f0f0f0; "
        "    border: 1px solid #cccccc; "
        "    border-radius: 4px; "
        "    margin: 2px; "
        "}"
        "QLabel { "
        "    border: none;"
        "    font-weight: bold; "
        "    color: #333333; "
        "    padding: 5px; "
        "    font-size: 12px; "
        "}"

    );
    QHBoxLayout *postLayout = new QHBoxLayout(postWidget);
    titleLabel = new QLabel(title);
    userIdLabel = new QLabel(userId);
    currentDateTimeLabel = new QLabel(currentDateTime);

    postLayout->addWidget(titleLabel);
    postLayout->addWidget(userIdLabel);
    postLayout->addWidget(currentDateTimeLabel);

    postLayout->setStretchFactor(titleLabel, 5);
    postLayout->setStretchFactor(userIdLabel, 2);
    postLayout->setStretchFactor(currentDateTimeLabel, 3);

    // 속성 설정
    postWidget->setProperty("postId", postId);
    postWidget->setProperty("title", title);
    postWidget->setProperty("content", content);
    postWidget->setProperty("currentDateTime", currentDateTime);

    postWidget->installEventFilter(this);

    postWidgets[postId] = postWidget;

    verticalLayout->addWidget(postWidget);

    totalPosts++;
}

void PostListWidget::removePostFromList(const QString &postId){
    if(postWidgets.contains(postId)){
        QWidget *postWidget = postWidgets[postId];

        postWidget->removeEventFilter(this);

        verticalLayout->removeWidget(postWidget);
        postWidget->deleteLater();

        postWidgets.remove(postId);

        totalPosts--;
    }
}

bool PostListWidget::eventFilter(QObject *obj, QEvent *event){
    if(event->type() == QEvent::MouseButtonPress){
        QWidget *widget = qobject_cast<QWidget*>(obj);
        if(widget){
            for (auto it = postWidgets.begin(); it != postWidgets.end(); ++it) {
                if (it.value() == widget) {
                    emit openPost(it.value());
                    break;
                }
            }
        }
    }
    return QWidget::eventFilter(obj, event);
}

void PostListWidget::getInfos(const QString &token, const QString &userId){
    this->token = token;
    this->userId = userId;
}
