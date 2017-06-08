#include "pop3.h"

pop3::pop3()
{
    QObject::connect(socket,SIGNAL(stateChanged(QAbstractSocket::SocketState)),
                     this,SLOT(onConnectionStateChanged(QAbstractSocket::SocketState)));
}

pop3::~pop3()
{
    socket->close();
}

bool pop3::waitForSocketReadyRead()
{
    if (!socket->waitForReadyRead(secondsToWait * 1000))
    {
        qDebug() << "Error222";
        return false;
    }
    return true;
}

bool pop3::login (QString host, int port, QString user, QString password)
{
    socket->connectToHostEncrypted(host, port);
    if (!socket->waitForConnected(secondsToWait * 1000))
    {
        qDebug() << "Error";
        return false;
    }

    if (!waitForSocketReadyRead()) return false;

    QString serverMessage;
    while (!serverMessage.contains("\n"))
    {serverMessage.append(socket->readAll());}

    if (!serverMessage.startsWith("+OK"))
    {
        qDebug() << "Error";
        return false;
    }

    socket->write( QString("USER "+user+"\n").toStdString().c_str());
    socket->flush();
    if (!waitForSocketReadyRead()) return false;

    serverMessage.clear();
    while (!serverMessage.contains("\n")) {serverMessage.append(socket->readAll());}

    if (!serverMessage.startsWith("+OK"))
    {
        qDebug() << "Error";
        return false;
    }

    socket->write(QString("PASS "+password+"\n").toStdString().c_str());
    if (!waitForSocketReadyRead()) return false;

    serverMessage.clear();
    while (!serverMessage.contains("\n")) {serverMessage.append(socket->readAll());}

    if (!serverMessage.startsWith("+OK"))
    {
        qDebug() << "Error";
        return false;
    }

    authenticated = true;
}

void pop3::logout()
{
    if (!authenticated) return;
    socket->write("QUIT\n");
    socket->flush();
    this->authenticated = false;
}

int pop3::getNumberOfEmails()
{
    if (!authenticated)
    {
        qDebug() << "Error";
        return -1;
    }
    socket->write("STAT\n");
    socket->flush();
    if (!waitForSocketReadyRead()) return -1;

    QString message;
    while (!message.contains("\n")) {message.append(socket->readAll());}

    if (!message.startsWith("+OK"))
    {
       qDebug() << "Error";
        return -1;
    }
    return message.split(" ")[1].toInt();
}


QVector<QString> pop3::getEmail(int index)
{
    QVector<QString> result, null;
    if (!authenticated)
    {
        qDebug() << "Error1";
        return null;
    }
    int emailNo = getNumberOfEmails();
    if (emailNo <= 0 || index > emailNo) return null;

    QString command = "RETR " + QString::number(index) + "\n";
    socket->write(command.toStdString().c_str());
    socket->flush();
    socket->waitForReadyRead(secondsToWait * 1000);


    QString information;
        char *byt = new char[2];
        while (!information.contains("\n"))
        {
            socket->read(byt,1);
            byt[1] = 0;
            information.append(byt);
        }
        delete[] byt;
    qDebug() << information;
    if (!information.startsWith("+OK"))
    {
        qDebug() << "Error3";
        return null;
    }


    socket->waitForReadyRead(secondsToWait * 1000);

    QString top = socket->readAll().data();
    qDebug() << top;
    top.section("\r\n",1);
    QByteArray header = top.toUtf8();
    qDebug() << header;
    QString decode_header = ReadMail::decodeWordSequence(header);
    QString date, from, subject;
    QRegularExpression sub("Subject: +(.*)");
    QRegularExpressionMatch match = sub.match(decode_header);
    if (match.hasMatch())
    {
        subject = match.captured(1);
        subject[subject.length() - 2] = '\0';
    }
    result.push_back(subject);
    QRegularExpression fr("From: +(.*)");
    QRegularExpressionMatch match2 = fr.match(decode_header);
    if (match2.hasMatch())
    {
        from = match2.captured(1);
        from[from.length() - 2] = '\0';
    }
    result.push_back(from);
    QRegularExpression d("Date: +(.*)");
    QRegularExpressionMatch match3 = d.match(decode_header);
    if (match3.hasMatch())
    {
        date = match3.captured(1);
        date[date.length() - 2] = '\0';
    }
    result.push_back(date);

    return result;
}

void pop3::onConnectionStateChanged (QAbstractSocket::SocketState state)
{
    if (state == QAbstractSocket::UnconnectedState)
        authenticated = false;
}
