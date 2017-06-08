#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H
#include "mainwindow.h"
#include <QDialog>
#include <QtNetwork/QAbstractSocket>
#include <QtNetwork/QSslSocket>
#include <QString>
#include <QTextStream>
#include <QDebug>
#include <QtWidgets/QMessageBox>
#include <QByteArray>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();
    //bool CheckExistEmail();

private slots:
    void on_CloseButton_clicked();

    void on_EnterButton_clicked();

    void on_PasswordLineEdit_textChanged();

    void on_LogonLineEdit_textChanged();

private:
    Ui::LoginWindow *ui;

};

#endif // LOGINWINDOW_H
