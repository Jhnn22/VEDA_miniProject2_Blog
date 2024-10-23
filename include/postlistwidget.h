#ifndef POSTLISTWIDGET_H
#define POSTLISTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
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
    void updatePostList(const QString &postId, const QString &title, const QString &content, const QString &currentDateTime);
    void removePostFromList(const QString &postId);
    bool eventFilter(QObject *obj, QEvent *event);

    void getUserId(const QString &userId);

    void updateUIAfterDelete(int pageNumber, int startIndex);
    void reorganizePages();

signals:
    void openPost(const Post &post);

private:
    Ui::PostListWidget *ui;

    QList<Post> postList;
    int totalPosts;
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel, *userIdLabel, *currentDateTimeLabel;
    QString userId;
};

#endif // POSTLISTWIDGET_H
