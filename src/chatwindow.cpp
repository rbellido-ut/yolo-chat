/**
 * @author Ronald Bellido
 */
#include "chatwindow.h"
#include "ui_chatwindow.h"

ChatWindow::ChatWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChatWindow)
{
    ui->setupUi(this);

    cDlg = new ClientSettingsDialog();
    sDlg = new ServerSettingsDialog();

    this->statusBar()->showMessage("Idle");

    QObject::connect(&client_, SIGNAL(statusChanged(QString)), this, SLOT(setStatus(const QString&)));
    QObject::connect(cDlg, SIGNAL(clientIgnite(QString, QString)), this, SLOT(startClient(const QString&, const QString&)));
    QObject::connect(sDlg, SIGNAL(serverIgnite(QString)), this, SLOT(startMuxServer(QString)));
}

ChatWindow::~ChatWindow()
{
    delete ui;
}

//Public slots implementation
/**
 * Slot that starts the chat client
 *
 * @author Ronald Bellido
 * @brief ChatWindow::startClient
 */
void ChatWindow::startClient(const QString& port, const QString& hostname) {
    client_.start_client(port.toInt(), hostname.toUtf8().constData());
}

/**
 * Slot that starts the multiplexing server
 *
 * @author Ronald Bellido
 * @brief ChatWindow::startMuxServer
 * @param port the port the server will listen for connections
 */
void ChatWindow::startMuxServer(const QString& port) {
    server_.start_server(port.toInt());
}

/**
 * Slot that sets the status bar to the specified string
 *
 * @author Ronald Bellido
 * @brief ChatWindow::setStatusBar
 * @param s the string to display
 */
void ChatWindow::setStatusBar(const QString &s) {
    this->statusBar()->showMessage(s);
}

//Private slots implementation
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
