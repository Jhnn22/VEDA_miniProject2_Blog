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
    void setButtons();
    void showPostDetail(const Post &post);

signals:
    void exit();

private:
    Ui::PostWidget *ui;

    CommentWidget *commentWidget;
};

#endif // POSTWIDGET_H
