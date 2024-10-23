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

signals:
    void commentRegisterAttempt(const QString &comment);
    void commentRegisterSuccess(const QString &comment);

private:
    Ui::CommentWidget *ui;
};

#endif // COMMENTWIDGET_H
