#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "client/client_net.h"
#include "server/server_net.h"
#include "clientsettingsdialog.h"
#include "serversettingsdialog.h"

namespace Ui {
class ChatWindow;
}

class ChatWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ChatWindow(QWidget *parent = 0);
    ~ChatWindow();
    void ErrorMsg(QString);

public slots:
    void startMuxServer(const QString &);
    void startClient(const QString &, const QString &);
    void setStatusBar(const QString &);
    
private slots:
    void on_sendButton_clicked();

    void on_actionExit_triggered();

    void on_actionClient_triggered();

    void on_actionServer_triggered();

private:
    Ui::ChatWindow *ui;

    //Keyboard events
    QKeyEvent *keyEvent;
    QString *textOfKeyPressed;

    //GUI objects
    ClientSettingsDialog *cDlg;
    ServerSettingsDialog *sDlg;

    //Networking objects
    ClientNetwork client_;
    ServerNetwork server_;

};

#endif // CHATWINDOW_H
