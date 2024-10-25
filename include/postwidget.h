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

    void setComments(const QString &postId);
    void loadComments(const QString &postId);
    void clearCurrentComment();
    void handleCommentListReceived(const QString &postId, const QJsonArray &comments);
    void handleCommentListError(const QString &error);

    void setButtons(QWidget *clickedPostWidget);
    void openPost_2(QWidget *clickedPostWidget);

    void getInfos(const QString &token, const QString &userId);
    void cleanupNetworkConnections();

signals:
    void exit();
    void editPostList(const QString &token, const QString &postId, const QString &title, const QString &content);
    void deletePostList(const QString &token, const QString &postId);

private:
    Ui::PostWidget *ui;

    CommentWidget *commentWidget;
    QMap<QString, CommentWidget*> commentWidgets;

    QString token, userId;
    bool isEditing;
    bool isButtonConnected;

    QString currentPostId;
};

#endif // POSTWIDGET_H
