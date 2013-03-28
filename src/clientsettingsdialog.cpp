#include "clientsettingsdialog.h"
#include "ui_clientsettingsdialog.h"

ClientSettingsDialog::ClientSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClientSettingsDialog)
{
    ui->setupUi(this);
}

ClientSettingsDialog::~ClientSettingsDialog()
{
    delete ui;
}

void ClientSettingsDialog::on_buttonBox_accepted()
{
    emit clientIgnite(ui->portInput->text(), ui->hostNameInput->text());
}
