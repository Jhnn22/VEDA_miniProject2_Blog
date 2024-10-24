#include "network.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrlQuery>
#include <QDateTime>

#include <QUuid>

Network *Network::m_instance = nullptr;

Network *Network::instance(){
    if(!m_instance){
        m_instance = new Network();
    }
    return m_instance;
}

Network::Network(QObject *parent) : QObject(parent){
    networkManager = new QNetworkAccessManager(this);
}

QJsonObject Network::byteArrayToJsonObject(const QByteArray &data){
    QJsonDocument doc = QJsonDocument::fromJson(data);
    return doc.object();
}

void Network::loginAttempt(const QString &id, const QString &pw){
    // emit loginSuccess("token", id, pw);
    QJsonObject jsonObject;
    jsonObject["id"] = id;
    jsonObject["password"] = pw;

    QNetworkRequest request(QUrl(QString(SERVER_URL) + "/user/login"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = networkManager->post(request, QJsonDocument(jsonObject).toJson());

    connect(reply, &QNetworkReply::finished, this, [=]() {
        if(reply->error() == QNetworkReply::NoError) {
            QJsonObject response = byteArrayToJsonObject(reply->readAll());
            if(response.contains("token")) {
                QString token = response["token"].toString();   // 토큰 추출
                emit loginSuccess(token, id, pw);
            } else {
                emit loginFailed("로그인 실패: 서버 응답 오류");
            }
        } else {
            QJsonObject errorResponse = byteArrayToJsonObject(reply->readAll());
            emit loginFailed(errorResponse["message"].toString());
        }
        reply->deleteLater();
    });
}

void Network::logoutAttempt(const QString &token){
    // emit logoutSuccess("");
    QNetworkRequest request(QUrl(QString(SERVER_URL) + "/user/logout"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", token.toUtf8());

    QNetworkReply *reply = networkManager->post(request, QByteArray());

    connect(reply, &QNetworkReply::finished, this, [=]() {
        if(reply->error() == QNetworkReply::NoError) {
            QJsonObject response = byteArrayToJsonObject(reply->readAll());
            if(response["status"].toString() == "Success") {
                emit logoutSuccess(token);
            } else {
                emit logoutFailed("로그아웃 실패: 서버 응답 오류");
            }
        } else {
            QJsonObject errorResponse = byteArrayToJsonObject(reply->readAll());
            emit logoutFailed(errorResponse["message"].toString());
        }
        reply->deleteLater();
    });
}

void Network::createAccountAttempt(const QString &id, const QString &pw){
    // emit createAccountSuccess();
    QJsonObject jsonObject;
    jsonObject["id"] = id;
    jsonObject["password"] = pw;
    jsonObject["nickname"] = id;    // 닉넴 id로 땜빵?
    jsonObject["is_manager"] = 0;

    QNetworkRequest request(QUrl(QString(SERVER_URL) + "/user/register"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = networkManager->post(request, QJsonDocument(jsonObject).toJson());

    connect(reply, &QNetworkReply::finished, this, [=]() {
        if(reply->error() == QNetworkReply::NoError) {
            QJsonObject response = byteArrayToJsonObject(reply->readAll());
            if(response["status"].toString() == "Success") {
                emit createAccountSuccess();
            } else {
                emit createAccountFailed("계정 생성 실패: 서버 응답 오류");
            }
        } else {
            QJsonObject errorResponse = byteArrayToJsonObject(reply->readAll());
            emit createAccountFailed(errorResponse["message"].toString());
        }
        reply->deleteLater();
    });
}

void Network::deleteAccountAttempt(const QString &token, const QString &id, const QString &pw){
    // emit deleteAccountSuccess(token);
    QJsonObject jsonObject;
    jsonObject["id"] = id;
    jsonObject["password"] = pw;

    QNetworkRequest request(QUrl(QString(SERVER_URL) + "/user/delete"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", token.toUtf8());

    QNetworkReply *reply = networkManager->post(request, QJsonDocument(jsonObject).toJson());

    connect(reply, &QNetworkReply::finished, this, [=]() {
        if(reply->error() == QNetworkReply::NoError) {
            QJsonObject response = byteArrayToJsonObject(reply->readAll());
            if(response["status"].toString() == "Success") {
                emit deleteAccountSuccess(token);
            } else {
                emit deleteAccountFailed("회원탈퇴 실패: 서버 응답 오류");
            }
        } else {
            QJsonObject errorResponse = byteArrayToJsonObject(reply->readAll());
            emit deleteAccountFailed(errorResponse["message"].toString());
        }
        reply->deleteLater();
    });
}

void Network::postRegisterAttempt(const QString &token, const QString &title, const QString &content, const QString &currentDateTime, const QString &userId){
    // const QString post_id = QUuid::createUuid().toString();
    // emit postRegisterSuccess(token, post_id, title, content, currentDateTime);
    QJsonObject jsonObject;
    jsonObject["title"] = title;
    jsonObject["content"] = content;
    jsonObject["file"] = QJsonArray();  // 빈 파일 배열

    QNetworkRequest request(QUrl(QString(SERVER_URL) + "/post/register"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = networkManager->post(request, QJsonDocument(jsonObject).toJson());

    connect(reply, &QNetworkReply::finished, this, [=]() {
        if(reply->error() == QNetworkReply::NoError) {
            QJsonObject response = byteArrayToJsonObject(reply->readAll());
            if(response["status"].toString() == "Success") {
                QString post_id = QString::number(response["post_id"].toInt());
                emit postRegisterSuccess(token, post_id, title, content, currentDateTime);
            } else {
                emit postRegisterFailed("게시글 등록 실패: 서버 응답 오류");
            }
        } else {
            QJsonObject errorResponse = byteArrayToJsonObject(reply->readAll());
            emit postRegisterFailed(errorResponse["message"].toString());
        }
        reply->deleteLater();
    });
}

void Network::postEditAttempt(const QString &token, const QString &postId, const QString &title, const QString &content, const QString &currentDateTime, const QString &userId){
    // emit postEditSuccess(token, postId, title, content, currentDateTime);
    QJsonObject jsonObject;
    jsonObject["id"] = postId.toInt();
    jsonObject["title"] = title;
    jsonObject["content"] = content;
    jsonObject["file"] = QJsonArray();  // 빈 파일 배열

    QNetworkRequest request(QUrl(QString(SERVER_URL) + "/post/modify"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = networkManager->post(request, QJsonDocument(jsonObject).toJson());

    connect(reply, &QNetworkReply::finished, this, [=]() {
        if(reply->error() == QNetworkReply::NoError) {
            QJsonObject response = byteArrayToJsonObject(reply->readAll());
            if(response["status"].toString() == "Success") {
                emit postEditSuccess(token, postId, title, content, currentDateTime);
            } else {
                emit postEditFailed("게시글 수정 실패: 서버 응답 오류");
            }
        } else {
            QJsonObject errorResponse = byteArrayToJsonObject(reply->readAll());
            emit postEditFailed(errorResponse["message"].toString());
        }
        reply->deleteLater();
    });
}

void Network::postDeleteAttempt(const QString &token, const QString &postId){
    // emit postDeleteSuccess(token, postId);
    QJsonObject jsonObject;
    jsonObject["id"] = postId.toInt();

    QNetworkRequest request(QUrl(QString(SERVER_URL) + "/post/delete"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = networkManager->post(request, QJsonDocument(jsonObject).toJson());

    connect(reply, &QNetworkReply::finished, this, [=]() {
        if(reply->error() == QNetworkReply::NoError) {
            QJsonObject response = byteArrayToJsonObject(reply->readAll());
            if(response["status"].toString() == "Success") {
                emit postDeleteSuccess(token, postId);
            } else {
                emit postDeleteFailed("게시글 삭제 실패: 서버 응답 오류");
            }
        } else {
            QJsonObject errorResponse = byteArrayToJsonObject(reply->readAll());
            emit postDeleteFailed(errorResponse["message"].toString());
        }
        reply->deleteLater();
    });
}

void Network::commentRegisterAttempt(const QString &token, const QString &postId, const QString &userId, const QString &comment){
    // emit commentRegisterSuccess(token, "1", comment);
    QJsonObject jsonObject;
    jsonObject["post_id"] = postId;
    jsonObject["author"] = userId;
    jsonObject["content"] = comment;

    QNetworkRequest request(QUrl(QString(SERVER_URL) + "/comment/insert"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = networkManager->post(request, QJsonDocument(jsonObject).toJson());

    connect(reply, &QNetworkReply::finished, this, [=]() {
        if(reply->error() == QNetworkReply::NoError) {
            QJsonObject response = byteArrayToJsonObject(reply->readAll());
            if(response["status"].toString() == "Success") {
                QString id = QString::number(response["id"].toInt());
                emit commentRegisterSuccess(token, id, comment);
            } else {
                emit commentRegisterFailed("댓글 등록 실패: 서버 응답 오류");
            }
        } else {
            QJsonObject errorResponse = byteArrayToJsonObject(reply->readAll());
            emit commentRegisterFailed(errorResponse["message"].toString());
        }
        reply->deleteLater();
    });
}


