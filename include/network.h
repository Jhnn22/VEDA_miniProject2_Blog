#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>

class Network : public QObject{
    Q_OBJECT

public:
    static Network *instance();

    void loginAttempt(const QString &id, const QString &pw);

    void createAccountAttempt(const QString &id, const QString &pw);

    void postRegisterAttempt(const QString &title, const QString &content, const QString &currentDateTime, const QString &userId);

    void postEditAttempt(const QString &postId, const QString &title, const QString &content, const QString &currentDateTime, const QString &userId);

    void postDeleteAttempt(const QString &postId);

    void commentRegisterAttempt(const QString &userId, const QString &comment);

signals:
    void loginSuccess(const QString &id);
    void loginFailed(const QString &errorMessage);

    void createAccountSuccess();
    void createAccountFailed(const QString &errorMessage);

    void postRegisterSuccess(const QString &postId, const QString &title, const QString &content, const QString &currentDateTime);
    void postRegisterFailed(const QString &errorMessage);

    void postEditSuccess(const QString &postId, const QString &title, const QString &content, const QString &currentDateTime);
    void postEditFailed(const QString &errorMessage);

    void postDeleteSuccess(const QString &postId);
    void postDeleteFailed(const QString &errorMessage);

    void commentRegisterSuccess(const QString &commentId, const QString &comment);
    void commentRegisterFailed(const QString &errorMessage);

private:
    explicit Network(QObject *parent = nullptr);
    static Network* m_instance;
};

#endif // NETWORK_H
