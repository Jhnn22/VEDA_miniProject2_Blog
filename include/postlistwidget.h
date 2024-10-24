#ifndef POSTLISTWIDGET_H
#define POSTLISTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QMap>

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
    void updatePostList(const QString &token, const QString &postId, const QString &title, const QString &content, const QString &currentDateTime);
    void removePostFromList(const QString &token, const QString &postId);
    void relocatePostListUI();
    bool eventFilter(QObject *obj, QEvent *event);

    void getInfos(const QString &token, const QString &userId);

    void updateUIAfterDelete(int pageNumber, int startIndex);
    void reorganizePages();

signals:
    void openPost(QWidget *clickedPostWidget);

private:
    Ui::PostListWidget *ui;

    int totalPosts;
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel, *userIdLabel, *currentDateTimeLabel;
    QMap<QString, QWidget*> postWidgets;
    QString token, userId;
};

#endif // POSTLISTWIDGET_H
