#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include "configmanager.h"
#include "languagesmanager.h"


namespace Ui {
class ConfigDialog;
}

class ConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigDialog(ConfigManager* manager, LanguagesManager lManager = LanguagesManager(), QWidget *parent = nullptr );
    ~ConfigDialog();
    void setMainTexts();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_toolButton_clicked();

private:
    Ui::ConfigDialog *ui;
    ConfigManager* managerHold;
    LanguagesManager langManager;

};

#endif // CONFIGDIALOG_H
