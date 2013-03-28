#ifndef CLIENTSETTINGSDIALOG_H
#define CLIENTSETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class ClientSettingsDialog;
}

class ClientSettingsDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ClientSettingsDialog(QWidget *parent = 0);
    ~ClientSettingsDialog();
    
private:
    Ui::ClientSettingsDialog *ui;
};

#endif // CLIENTSETTINGSDIALOG_H
