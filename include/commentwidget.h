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

    void getUserId(const QString &userId);

private:
    Ui::CommentWidget *ui;

    QString userId;
};

#endif // COMMENTWIDGET_H
