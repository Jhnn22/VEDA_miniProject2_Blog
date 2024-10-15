#ifndef WRITEWIDGET_H
#define WRITEWIDGET_H

#include <QWidget>

namespace Ui {
class WriteWidget;
}

class WriteWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WriteWidget(QWidget *parent = nullptr);
    ~WriteWidget();

private:
    Ui::WriteWidget *ui;
};

#endif // WRITEWIDGET_H
