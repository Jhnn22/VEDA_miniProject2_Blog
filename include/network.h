#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#define SERVER_URL "http://"

class Network : public QObject{
    Q_OBJECT

public:
    static Network *instance();

    void loginAttempt(const QString &id, const QString &pw);

    void logoutAttempt(const QString &token);

    void createAccountAttempt(const QString &id, const QString &pw);

    void deleteAccountAttempt(const QString &token, const QString &id, const QString &pw);

    void postRegisterAttempt(const QString &token, const QString &title, const QString &content, const QString &currentDateTime, const QString &userId);

    void postEditAttempt(const QString &token, const QString &postId, const QString &title, const QString &content, const QString &currentDateTime, const QString &userId);

    void postDeleteAttempt(const QString &token, const QString &postId);

    void commentRegisterAttempt(const QString &token, const QString &postId, const QString &userId, const QString &comment);

signals:
    void loginSuccess(const QString &token, const QString &id, const QString &pw);
    void loginFailed(const QString &errorMessage);

    void logoutSuccess(const QString &token);
    void logoutFailed(const QString &errorMessage);

    void createAccountSuccess();
    void createAccountFailed(const QString &errorMessage);

    void deleteAccountSuccess(const QString &token);
    void deleteAccountFailed(const QString &token);

    void postRegisterSuccess(const QString &token, const QString &postId, const QString &title, const QString &content, const QString &currentDateTime);
    void postRegisterFailed(const QString &errorMessage);

    void postEditSuccess(const QString &token, const QString &postId, const QString &title, const QString &content, const QString &currentDateTime);
    void postEditFailed(const QString &errorMessage);

    void postDeleteSuccess(const QString &token, const QString &postId);
    void postDeleteFailed(const QString &errorMessage);

    void commentRegisterSuccess(const QString &token, const QString &commentId, const QString &comment);
    void commentRegisterFailed(const QString &errorMessage);

private:
    explicit Network(QObject *parent = nullptr);
    static Network* m_instance;

    QNetworkAccessManager *networkManager;
    QJsonObject byteArrayToJsonObject(const QByteArray &data);
};

#endif // NETWORK_H
