#ifndef COMMENTWIDGET_H
#define COMMENTWIDGET_H

#include <QWidget>
#include <QSpacerItem>
#include <QVBoxLayout>

class CommentDisplayWidget;

namespace Ui {
class CommentWidget;
}

class CommentWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CommentWidget(QWidget *parent = nullptr);
    ~CommentWidget();

    void setButtons();
    void setupLayout();
    void getInfos(const QString &token, const QString &postId, const QString &userId);
    void clearComments();
    void addComment(const QString &commentId, const QString &content, const QString &author, const QString &time);

private:
    Ui::CommentWidget *ui;

    QString token, userId, postId;
    QVBoxLayout *commentsLayout;
    QMap<QString, QWidget*> commentItems;
};

#endif // COMMENTWIDGET_H
