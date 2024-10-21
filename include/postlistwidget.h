#ifndef POSTLISTWIDGET_H
#define POSTLISTWIDGET_H

#include <QWidget>
#include <QDateTime>

namespace Ui {
class PostListWidget;
}

class PostListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PostListWidget(QWidget *parent = nullptr);
    ~PostListWidget();

    void setPostList(const QString &title, const QString &content);

    bool eventFilter(QObject *obj, QEvent *event);
    void showPostDetail(int index);


private:
    Ui::PostListWidget *ui;

    struct Post{
        QString title;
        QString content;
        QDateTime date;
    };
    QList<Post> postList;
};

#endif // POSTLISTWIDGET_H
