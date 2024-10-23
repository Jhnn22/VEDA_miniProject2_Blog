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

    void setInputFields(const QString &comment);
    void setButtons();

private:
    Ui::CommentDisplayWidget *ui;
};

#endif // COMMENTDISPLAYWIDGET_H
