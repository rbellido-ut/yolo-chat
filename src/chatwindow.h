#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMainWindow>
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
    
private slots:
    void on_sendButton_clicked();
    void on_actionExit_triggered();

    void on_actionClient_triggered();

    void on_actionServer_triggered();

private:
    Ui::ChatWindow *ui;

    //GUI objects
    ClientSettingsDialog *cDlg;
    ServerSettingsDialog *sDlg;

    //Networking objects
    ClientNetwork client_;
    ServerNetwork server_;

};

#endif // CHATWINDOW_H
