#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMainWindow>
#include "client/client_net.h"
#include "server/server_net.h"

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

private:
    Ui::ChatWindow *ui;
    ClientNetwork *client_;
    ServerNetwork *server_;

};

#endif // CHATWINDOW_H
