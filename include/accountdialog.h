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
    void clearLoginInputFields();
    void clearCreateAccountInputFields();
    void setButtons();

signals:
    void loginSuccess_2(const QString &token, const QString &id);

public slots:
    void openAccountDialog();

private:
    Ui::AccountDialog *ui;
};

#endif // ACCOUNTDIALOG_H
