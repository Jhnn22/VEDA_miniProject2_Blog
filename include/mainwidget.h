#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

class WriteWidget;
class AccountDialog;
class PostListWidget;
class PostWidget;

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

    void setPages();
    void setButtons();
    void updateButtons();

private:
    Ui::MainWidget *ui;

    WriteWidget *writeWidget;
    AccountDialog *accountDialog;
    PostListWidget *postListWidget;
    PostWidget *postWidget;

    QString token, userId;

    bool isLoggedIn;
};

#endif // MAINWIDGET_H
