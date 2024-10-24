#ifndef COMMENTWIDGET_H
#define COMMENTWIDGET_H

#include <QWidget>
#include <QSpacerItem>

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

    void getInfos(const QString &token, const QString &userId);
    void getPostId(const QString &postId);

private:
    Ui::CommentWidget *ui;

    QString token, userId, postId;
};

#endif // COMMENTWIDGET_H
