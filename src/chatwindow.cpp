#include "chatwindow.h"
#include "ui_chatwindow.h"

ChatWindow::ChatWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChatWindow)
{
    ui->setupUi(this);

}

ChatWindow::~ChatWindow()
{
    delete ui;
}

void ChatWindow::on_sendButton_clicked()
{
    //send text in textbox to socket
}

void ChatWindow::on_actionExit_triggered()
{
    qApp->quit();
}
