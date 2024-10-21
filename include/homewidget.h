#ifndef HOMEWIDGET_H
#define HOMEWIDGET_H

#include <QWidget>

class AccountDialog;
class PostListWidget;

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
    void write();

public slots:
    void handleLoginResult();
    void updatePostList(const QString &title, const QString &content);

private:
    Ui::HomeWidget *ui;

    AccountDialog *accountDialog;
    PostListWidget *postListWidget;

    bool isLoggedIn;
};

#endif // HOMEWIDGET_H
