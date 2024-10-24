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

    void getInfos(const QString &token, const QString &userId);

private:
    Ui::CommentDisplayWidget *ui;

    QString token, userId;
};

#endif // COMMENTDISPLAYWIDGET_H
