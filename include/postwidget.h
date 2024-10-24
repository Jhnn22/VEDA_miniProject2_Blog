#ifndef POSTWIDGET_H
#define POSTWIDGET_H

#include <QWidget>

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
    void setButtons(QWidget *clickedPostWidget);
    void openPost_2(QWidget *clickedPostWidget);

    void getInfos(const QString &token, const QString &userId);

signals:
    void exit();
    void editPostList(const QString &token, const QString &postId, const QString &title, const QString &content, const QString &currentDateTime);
    void deletePostList(const QString &token, const QString &postId);

private:
    Ui::PostWidget *ui;

    CommentWidget *commentWidget;

    QString token, userId;
    bool isEditing;
    bool isButtonConnected;
};

#endif // POSTWIDGET_H
