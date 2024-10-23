#ifndef POSTWIDGET_H
#define POSTWIDGET_H

#include <QWidget>
#include "post.h"

class CommentWidget;

namespace Ui {
class PostWidget;
}

class PostWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PostWidget(QWidget *parent = nullptr);
    ~PostWidget();

    void setComments();
    void setButtons(const Post &post);
    void openPost_2(const Post &post);

    void getUserId(const QString &userId);

signals:
    void exit();
    void editPostList(const QString &postId, const QString &title, const QString &content, const QString &currentDateTime);
    void deletePostList(const QString &postId);

private:
    Ui::PostWidget *ui;

    CommentWidget *commentWidget;

    QString userId;
    bool isEditing;
    bool isButtonConnected;
};

#endif // POSTWIDGET_H
