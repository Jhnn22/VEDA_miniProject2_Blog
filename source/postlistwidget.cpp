#include "postlistwidget.h"
#include "ui_postlistwidget.h"
#include "network.h"
#include <QHBoxLayout>
#include <QJsonArray>
#include <QJsonObject>
#define POSTS_PER_PAGE 10

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

void PostListWidget::removePostFromList(const QString &token, const QString &postId){
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
        if(token.isEmpty()){
            return true;
        }
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

void PostListWidget::refreshPostList(const QString &token){
    connect(Network::instance(), &Network::postListReceived, this, &PostListWidget::handlePostListReceived);
    connect(Network::instance(), &Network::postListFailed, this, &PostListWidget::handlePostListError);

    Network::instance()->requestPostList(token);
}

void PostListWidget::clearPostList() {
    // 기존 위젯들 제거
    for (QWidget* widget : postWidgets.values()) {
        widget->removeEventFilter(this);
        verticalLayout->removeWidget(widget);
        widget->deleteLater();
    }

    postWidgets.clear();
    totalPosts = 0;

    // 첫 페이지만 남기고 나머지 페이지 제거
    while (ui->stackedWidget->count() > 1) {
        QWidget* widget = ui->stackedWidget->widget(ui->stackedWidget->count() - 1);
        ui->stackedWidget->removeWidget(widget);
        delete widget;
    }
    ui->stackedWidget->setCurrentIndex(0);
}

void PostListWidget::handlePostListReceived(const QJsonArray &posts) {
    clearPostList();

    for (const QJsonValue &postVal : posts) {
        QJsonObject post = postVal.toObject();
        QString postId = post["id"].toString();
        QString title = post["title"].toString();
        QString content = post["content"].toString();
        QString currentDateTime = post["update_date"].toString();
        QString authorId = post["author"].toString();

        // 새 페이지 생성 필요 여부 확인
        if (totalPosts % POSTS_PER_PAGE == 0 && totalPosts > 0) {
            makePage();
        }

        // 게시글 위젯 생성
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
        QLabel *userIdLabel = new QLabel(authorId);
        QLabel *currentDateTimeLabel = new QLabel(currentDateTime);

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
        postWidget->setProperty("authorId", authorId);

        postWidget->installEventFilter(this);

        postWidgets[postId] = postWidget;
        verticalLayout->addWidget(postWidget);

        totalPosts++;
    }

    // 시그널 연결 해제
    disconnect(Network::instance(), &Network::postListReceived,
               this, &PostListWidget::handlePostListReceived);
    disconnect(Network::instance(), &Network::postListFailed,
               this, &PostListWidget::handlePostListError);
}

void PostListWidget::handlePostListError(const QString &error) {
    qDebug() << "게시글 목록 로드 실패" << error;

    // 시그널 연결 해제
    disconnect(Network::instance(), &Network::postListReceived,
               this, &PostListWidget::handlePostListReceived);
    disconnect(Network::instance(), &Network::postListFailed,
               this, &PostListWidget::handlePostListError);
}
