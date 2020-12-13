#include "configdialog.h"
#include "ui_configdialog.h"

ConfigDialog::ConfigDialog(ConfigManager* manager, LanguagesManager lManager, QWidget *parent  ) :
    QDialog(parent),
    ui(new Ui::ConfigDialog)
{
    ui->setupUi(this);

    managerHold = manager;
    langManager = lManager;
    setMainTexts();
    ui->inputIndexBookFile->setText( manager->getIndexBookFilename() );
    ui->autosaveCheckbox->setChecked( manager->getAutosaveValue() );
    QStringList languagesList;
    languagesList << "English" << "Italian";

    ui->comboLanguage->addItems( languagesList );
    ui->comboLanguage->setCurrentIndex( manager->getLanguage() );

}

ConfigDialog::~ConfigDialog()
{
    delete ui;
}

void ConfigDialog::on_buttonBox_accepted()
{
    managerHold->setIndexBookFilename( ui->inputIndexBookFile->text() );
    managerHold->setAutosaveValue( ui->autosaveCheckbox->checkState() == Qt::Checked ? true : false );
    managerHold->setLanguage( ui->comboLanguage->currentIndex() );
    managerHold->save();

    this->close();
}

void ConfigDialog::on_buttonBox_rejected()
{
    this->close();
}

void ConfigDialog::on_toolButton_clicked()
{
    ui->inputIndexBookFile->setText( QFileDialog::getSaveFileName( this, "Select file" ) );
}

void ConfigDialog::setMainTexts() {
    ui->groupBoxFileConfig->setTitle( langManager.getText( FILE_CONFIG_STR ) );
    ui->labelStandardFile->setText( langManager.getText( STANDARD_FILE_TO_LOAD_STR ) );
    ui->autosaveCheckbox->setText( langManager.getText( AUTOSAVE_STR ) );
    ui->groupBoxLanguage->setTitle( langManager.getText( LANGUAGE_STR ) );
    ui->labelSelectLanguage->setText( langManager.getText( SELECT_LANGUAGE_STR ) );
    this->setWindowTitle( langManager.getText( CONFIG_DIALOG_TITLE_STR ) );
}
