#ifndef POST_H
#define POST_H

#include <QString>
#include <QDateTime>

struct Post{
    QString title;
    QString content;
    QDateTime date;
};

#endif // POST_H
