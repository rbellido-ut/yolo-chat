#include "chatwindow.h"
#include "ui_chatwindow.h"

ChatWindow::ChatWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChatWindow)
{
    ui->setupUi(this);

    cDlg = new ClientSettingsDialog();
    sDlg = new ServerSettingsDialog();
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

void ChatWindow::on_actionClient_triggered()
{
    cDlg->show();
}

void ChatWindow::on_actionServer_triggered()
{
    sDlg->show();
}
