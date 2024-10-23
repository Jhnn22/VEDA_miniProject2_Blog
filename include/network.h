#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>

class Network : public QObject{
    Q_OBJECT

public:
    void loginAttempt(const QString &id, const QString &pw){
        emit loginSuccess(id);
        // emit loginFailed("아이디 또는 비밀번호가 일치하지 않습니다.");
    }

    void createAccountAttempt(const QString &id, const QString &pw){
        emit createAccountSuccess();
        // emit createAccountFailed("아이디가 이미 존재합니다.");
    }

signals:
    void loginSuccess(const QString &id);
    void loginFailed(const QString &errorMessage);

    void createAccountSuccess();
    void createAccountFailed(const QString &errorMessage);
};

#endif // NETWORK_H
