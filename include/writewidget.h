#ifndef WRITEWIDGET_H
#define WRITEWIDGET_H

#include <QWidget>

class QLineEdit;
class QTextEdit;

namespace Ui {
class WriteWidget;
}

class WriteWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WriteWidget(QWidget *parent = nullptr);
    ~WriteWidget();

    void setInputFields();
    void clearInputFields();
    void setButtons();

    void getInfos(const QString &token, const QString &userId);

signals:
    void exit();
    void postRegisterSuccess_2(const QString &token, const QString &postId, const QString &title, const QString &content, const QString &currentDateTime);

private:
    Ui::WriteWidget *ui;

    QString token, userId;
};

#endif // WRITEWIDGET_H
