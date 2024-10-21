#include "postlistwidget.h"
#include "ui_postlistwidget.h"
#include <QHBoxLayout>
#include <QLabel>

PostListWidget::PostListWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PostListWidget)
{
    ui->setupUi(this);

}

PostListWidget::~PostListWidget()
{
    delete ui;
}

void PostListWidget::setPostList(const QString &title, const QString &content){
    // 테스트용 데이터
    Post newPost;
    newPost.title = title;
    newPost.content = content;
    newPost.date = QDateTime::currentDateTime();
    postList.append(newPost);

    QWidget *postWidget = new QWidget(this);
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

    postWidget->setProperty("index", postList.size() - 1); // 위젯에 인덱스 속성 추가

    postWidget->installEventFilter(this);

    ui->verticalLayout->addWidget(postWidget);

}

bool PostListWidget::eventFilter(QObject *obj, QEvent *event){
    if(event->type() == QEvent::MouseButtonPress){
        QWidget *widget = qobject_cast<QWidget*>(obj);
        if(widget){
            int index = widget->property("index").toInt();
            if(index >= 0 && index < postList.size()){
                showPostDetail(index);
            }
        }
    }
    return QWidget::eventFilter(obj, event);
}

void PostListWidget::showPostDetail(int index){
    Post checkPost = postList.at(index);

    qDebug() << "---------------------";
    qDebug() << "제목: " + checkPost.title;
    qDebug() << "작성일: " + checkPost.date.toString("MM-dd HH:mm");
    qDebug() << "내용: " + checkPost.content;


}
