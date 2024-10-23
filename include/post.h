#ifndef POST_H
#define POST_H

#include <QString>
#include <QDateTime>

struct Post{
    QString postId;
    QString title;
    QString content;
    QString currentDateTime;
};

#endif // POST_H
