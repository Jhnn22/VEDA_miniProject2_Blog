#ifndef POSTLISTWIDGET_H
#define POSTLISTWIDGET_H

#include <QWidget>
#include <QDateTime>
#include <QFrame>
#include <QVBoxLayout>
#include "post.h"

namespace Ui {
class PostListWidget;
}

class PostListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PostListWidget(QWidget *parent = nullptr);
    ~PostListWidget();

    void makePage();
    void setButtons();
    void setPostList(const QString &title, const QString &content);


    bool eventFilter(QObject *obj, QEvent *event);

signals:
    void openPostWidget(const Post &post);

private:
    Ui::PostListWidget *ui;

    QList<Post> postList;
    QWidget *page;
    QFrame *frame;
    QVBoxLayout *pageLayout, *verticalLayout;
    int totalPosts;

};

#endif // POSTLISTWIDGET_H
