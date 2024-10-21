#ifndef ACCOUNTDIALOG_H
#define ACCOUNTDIALOG_H

#include <QDialog>

namespace Ui {
class AccountDialog;
}

class AccountDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AccountDialog(QWidget *parent = nullptr);
    ~AccountDialog();

    void setInputFields();
    void setButtons();

signals:
    // 네트워크 클래스와 데이터 통신
    void loginAttempt();
    void loginSuccess();

public slots:
    void openAccountDialog();

private:
    Ui::AccountDialog *ui;
};

#endif // ACCOUNTDIALOG_H
