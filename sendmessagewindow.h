#ifndef SENDMESSAGEWINDOW_H
#define SENDMESSAGEWINDOW_H

#include <QDialog>
#include <QtNetwork/QAbstractSocket>
#include <QtNetwork/QSslSocket>
#include <QString>
#include <QTextStream>
#include <QDebug>
#include <QtWidgets/QMessageBox>
#include <QByteArray>

namespace Ui {
class SendMessageWindow;
}

class SendMessageWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SendMessageWindow(QWidget *parent = 0);
    ~SendMessageWindow();
    void initSMTP(const QString &user, const QString &pass, const QString &host, int port = 465, int timeout = 30000);
    void sendMail( const QString &from, const QString &to, const QString &subject, const QString &body);
    void DeleteSMTP();
    void initLogPas(QString pas, QString log);

signals:
    void status( const QString &);
private slots:
    void on_SendButton_clicked();

    void stateChanged(QAbstractSocket::SocketState socketState);
    void errorReceived(QAbstractSocket::SocketError socketError);
    void disconnected();
    void connected();
    void readyRead();
private:
    Ui::SendMessageWindow *ui;

    int timeout;
    QString message;
    QTextStream *t;
    QSslSocket *socket;
    QString from;
    QString rcpt;
    QString response;
    QString user;
    QString pass;
    QString host;
    int port;
    enum states{Tls, HandShake ,Auth,User,Pass,Rcpt,Mail,Data,Init,Body,Quit,Close};
    int state;
    bool SucFlag;
};

#endif // SENDMESSAGEWINDOW_H
