#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include <QDebug>
#include "sendmessagewindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose, true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_FileClose_triggered()
{
    close();
}

void MainWindow::SetLogPass(QString pass, QString log)
{
    this->password = pass;
    this->login = log;
}

void MainWindow::on_IncomingMessageButton_clicked()
{
    pop3 *pop3_obj = new pop3();
    pop3_obj->login("pop.mail.ru", 995, this->login, this->password);
//    int j = 1;
//    for(int i = pop3_obj->getNumberOfEmails(); i >= 0; i--)
//    {
//        QVector<QString> messages = pop3_obj->getEmail(i);
//        ui->TextEdit->setText(QString::number(j++) + messages.takeAt(0) + messages.takeAt(1) + messages.takeAt(2));
//    }
    pop3_obj->logout();
}

void MainWindow::on_WriteMessageButton_clicked()
{
    SendMessageWindow *smw = new SendMessageWindow();
    smw->initLogPas(this->password, this->login);
    smw->show();
}

void MainWindow::on_EnterTheMessage_triggered()
{
    on_WriteMessageButton_clicked();
}
