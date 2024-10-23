#include "network.h"
#include <QUuid>    // 테스트

Network *Network::m_instance = nullptr;

Network *Network::instance(){
    if(!m_instance){
        m_instance = new Network();
    }
    return m_instance;
}

Network::Network(QObject *parent) : QObject(parent){
    // 필요한 초기화 코드가 있다면 여기 추가
}

void Network::loginAttempt(const QString &id, const QString &pw){
    emit loginSuccess(id);
    // emit loginFailed("아이디 또는 비밀번호가 일치하지 않습니다.");
}


void Network::createAccountAttempt(const QString &id, const QString &pw){
    emit createAccountSuccess();
    // emit createAccountFailed("아이디가 이미 존재합니다.");
}

void Network::postRegisterAttempt(const QString &title, const QString &content, const QString &currentDateTime, const QString &userId){
    const QString postId = QUuid::createUuid().toString();  // 테스트 코드
    emit postRegisterSuccess(postId, title, content, currentDateTime);
    // emit postRegisterFailed("게시글 등록 실패");
}

void Network::postEditAttempt(const QString &postId, const QString &title, const QString &content, const QString &currentDateTime, const QString &userId){
    emit postEditSuccess(postId, title, content, currentDateTime);
    // emit postEditFailed("게시글 편집 실패");
}

void Network::postDeleteAttempt(const QString &postId){
    emit postDeleteSuccess(postId);
    // emit postDeleteFailed("게시글 삭제 실패");
}

void Network::commentRegisterAttempt(const QString &userId, const QString &comment){
    const QString commentId = "고유 댓글 ID 발급";
    emit commentRegisterSuccess(commentId, comment);
    // emit commentRegisterSuccess("댓글 등록 실패");
}


