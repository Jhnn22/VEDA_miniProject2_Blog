#ifndef HOMEWIDGET_H
#define HOMEWIDGET_H

#include <QWidget>
#include "post.h"

class AccountDialog;
class PostListWidget;
class PostWidget;

namespace Ui {
class HomeWidget;
}

class HomeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HomeWidget(QWidget *parent = nullptr);
    ~HomeWidget();

    void setPages();
    void setButtons();
    void updateButtons();

signals:
    void loginSuccess_3(const QString &id);
    void openWriteWidget();

public slots:
    void updatePostList(const QString &title, const QString &content);

private:
    Ui::HomeWidget *ui;

    AccountDialog *accountDialog;
    PostListWidget *postListWidget;
    PostWidget *postWidget;

    bool isLoggedIn;
};

#endif // HOMEWIDGET_H
