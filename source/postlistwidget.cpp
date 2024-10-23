#include "postlistwidget.h"
#include "ui_postlistwidget.h"
#include <QHBoxLayout>
#include <QLabel>
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
    page = new QWidget(this);
    pageLayout = new QVBoxLayout(page);
    pageLayout->setContentsMargins(0, 0, 0, 0);
    frame = new QFrame(page);
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

void PostListWidget::setPostList(const QString &title, const QString &content){
    Post newPost;
    newPost.title = title;
    newPost.content = content;
    newPost.date = QDateTime::currentDateTime();
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
    QLabel *titleLabel = new QLabel(title);
    QLabel *dateLabel = new QLabel(newPost.date.toString("MM-dd HH:mm"));
    postLayout->addWidget(titleLabel);
    postLayout->addWidget(dateLabel);
    postLayout->setStretchFactor(titleLabel, 7);
    postLayout->setStretchFactor(dateLabel, 3);

    // 페이지 별 인덱스 적용
    postWidget->setProperty("pageIndex", (totalPosts - 1) % POSTS_PER_PAGE);
    postWidget->setProperty("pageNumber", (totalPosts - 1) / POSTS_PER_PAGE);

    postWidget->installEventFilter(this);

    verticalLayout->addWidget(postWidget);

}

bool PostListWidget::eventFilter(QObject *obj, QEvent *event){
    if(event->type() == QEvent::MouseButtonPress){
        QWidget *widget = qobject_cast<QWidget*>(obj);
        if(widget){
            int pageNumber = widget->property("pageNumber").toInt();
            int pageIndex = widget->property("pageIndex").toInt();
            int totalIndex = (pageNumber * POSTS_PER_PAGE) + pageIndex;
            if(totalIndex >= 0 && totalIndex < postList.size()){
                emit openPostWidget(postList[totalIndex]);
            }
        }
    }
    return QWidget::eventFilter(obj, event);
}

