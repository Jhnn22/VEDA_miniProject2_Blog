#ifndef COMMENTDISPLAYWIDGET_H
#define COMMENTDISPLAYWIDGET_H

#include <QWidget>

namespace Ui {
class CommentDisplayWidget;
}

class CommentDisplayWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CommentDisplayWidget(QWidget *parent = nullptr);
    ~CommentDisplayWidget();

    void setInputFields(const QString &commentId, const QString &userId, const QString &comment);
    void setButtons();

    void getUserId(const QString &userId);

private:
    Ui::CommentDisplayWidget *ui;

    QString userId;
};

#endif // COMMENTDISPLAYWIDGET_H
