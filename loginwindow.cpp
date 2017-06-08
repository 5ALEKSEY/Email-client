#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QDebug>

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    setAttribute(Qt::WA_DeleteOnClose, true);
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_CloseButton_clicked()
{
    close();
}

void LoginWindow::on_EnterButton_clicked()
{
    MainWindow *window = new MainWindow();
    window->show();
    window->SetLogPass(ui->PasswordLineEdit->text(), ui->LogonLineEdit->text() + ui->checkPort->currentText());
    close();
}

void LoginWindow::on_PasswordLineEdit_textChanged()
{
    if (ui->PasswordLineEdit->text().isEmpty())
        ui->EnterButton->setEnabled(false);
    else
        ui->EnterButton->setEnabled(true);
}

void LoginWindow::on_LogonLineEdit_textChanged()
{
    if (ui->LogonLineEdit->text().isEmpty())
        ui->EnterButton->setEnabled(false);
    else
        ui->EnterButton->setEnabled(true);
}

//bool LoginWindow::CheckExistEmail()
//{

//}
