#ifndef POP3_H
#define POP3_H

#include <QObject>
#include <QTcpSocket>
#include <QSslSocket>
#include <QDebug>
#include <QDataStream>
#include <QStringList>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QTextCodec>
#include <QTime>
#include <QDate>
#include <QPair>
#include <QVector>
#include <QErrorMessage>
#include "pop3_commands.h"
#include "readmail.h"

class pop3 : public QObject
{
    Q_OBJECT
private:
    QSslSocket *socket = new QSslSocket();

    int secondsToWait = 5;
    bool authenticated = false;
    bool waitForSocketReadyRead ();
    QVector< QPair<QString,QString> > uIdList;
    int num;

public:
    pop3();
    ~pop3();

    bool login (QString host, int port, QString user, QString password);
    void logout ();
    int getNumberOfEmails();
    QVector<QString> getEmail(int index);


private slots:
    void onConnectionStateChanged(QAbstractSocket::SocketState state);

signals:
};



#endif // POP3_H
