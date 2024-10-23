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
    for(auto &post : postList){
        if(post.postId == postId){
            post.title = title;
            post.content = content;
            post.currentDateTime = currentDateTime;

            titleLabel->setText(title);
            userIdLabel->setText(userId);
            currentDateTimeLabel->setText(currentDateTime);

            return;
        }
    }

    Post newPost;
    newPost.postId = postId;
    newPost.title = title;
    newPost.content = content;
    newPost.currentDateTime = currentDateTime;
    postList.append(newPost);

    totalPosts = postList.size();
    if(totalPosts % POSTS_PER_PAGE == 1 && totalPosts > POSTS_PER_PAGE){
        makePage();
    }

    QWidget *postWidget = new QWidget();
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

    // 페이지 별 인덱스 적용
    postWidget->setProperty("pageNumber", (totalPosts - 1) / POSTS_PER_PAGE);
    postWidget->setProperty("pageIndex", (totalPosts - 1) % POSTS_PER_PAGE);

    postWidget->installEventFilter(this);

    verticalLayout->addWidget(postWidget);
}

void PostListWidget::removePostFromList(const QString &postId){
    int deletedIndex = -1;

    // 삭제할 게시글의 인덱스 찾기
    for(int i = 0; i < postList.size(); i++) {
        if(postList[i].postId == postId) {
            deletedIndex = i;
            break;
        }
    }

    if(deletedIndex != -1) {
        // 게시글 삭제
        postList.removeAt(deletedIndex);
        totalPosts--;

        // 게시글 목록 삭제

    }
}

bool PostListWidget::eventFilter(QObject *obj, QEvent *event){
    if(event->type() == QEvent::MouseButtonPress){
        QWidget *widget = qobject_cast<QWidget*>(obj);
        if(widget){
            int pageNumber = widget->property("pageNumber").toInt();
            int pageIndex = widget->property("pageIndex").toInt();
            int totalIndex = (pageNumber * POSTS_PER_PAGE) + pageIndex;
            if(totalIndex >= 0 && totalIndex < postList.size()){
                emit openPost(postList[totalIndex]);
            }
        }
    }
    return QWidget::eventFilter(obj, event);
}

void PostListWidget::getUserId(const QString &userId){
    this->userId = userId;
}
