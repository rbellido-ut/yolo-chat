#include "serversettingsdialog.h"
#include "ui_serversettingsdialog.h"

ServerSettingsDialog::ServerSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServerSettingsDialog)
{
    ui->setupUi(this);
}

ServerSettingsDialog::~ServerSettingsDialog()
{
    delete ui;
}

void ServerSettingsDialog::on_buttonBox_accepted()
{
    emit serverIgnite(ui->portInput->text());
}
