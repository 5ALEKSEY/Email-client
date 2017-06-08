#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "pop3.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void SetLogPass(QString pass, QString log);
private slots:
    void on_FileClose_triggered();

    void on_IncomingMessageButton_clicked();

    void on_WriteMessageButton_clicked();

    void on_EnterTheMessage_triggered();

private:
    Ui::MainWindow *ui;
    QString password;
    QString login;
};

#endif // MAINWINDOW_H
