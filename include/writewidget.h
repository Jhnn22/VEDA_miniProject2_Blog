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
    void setButtons();
    void setToolButtons();

signals:
    void exit();
    // 네트워크 클래스와 데이터 통신
    void postRegisterAttempt(const QString &title, const QString &content);
    void postRegisterSuccess(const QString &title, const QString &content);

private:
    Ui::WriteWidget *ui;
};

#endif // WRITEWIDGET_H
