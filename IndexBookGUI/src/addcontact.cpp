#include "addcontact.h"
#include "ui_addcontact.h"

AddContact::AddContact( QWidget *parent, LanguagesManager lManager ) :
    QDialog(parent),
    ui(new Ui::AddContact)
{
    ui->setupUi(this);
    langManager = lManager;
    setMainTexts();
    loadBirthdayCombos();
    dataAccepted = false;
    AddedPerson = Person();
    editMode = false;

}

AddContact::AddContact(Person personToModify, QWidget *parent,LanguagesManager lManager ) :
    QDialog ( parent ),
    ui(new Ui::AddContact)
{
    ui->setupUi(this);
    langManager = lManager;
    setMainTexts();
    loadBirthdayCombos();
    dataAccepted = false;
    AddedPerson = Person();
    editMode = true;
    ui->inputName->setText( QString::fromStdString( personToModify.getName() ) );
    ui->inputSurname->setText( QString::fromStdString( personToModify.getSurname() ) );
    ui->inputTelephone->setText( QString::fromStdString( personToModify.getTelephone() ) );
    ui->inputEmail->setText( QString::fromStdString( personToModify.getEmail() ) );
    ui->comboDay->setCurrentIndex( ui->comboDay->findText( QString::number( personToModify.getBirthdate().getDay() ) ) );
    ui->comboYear->setCurrentIndex( ui->comboYear->findText( QString::number( personToModify.getBirthdate().getYear() ) ) );
    ui->comboMonth->setCurrentIndex( static_cast<unsigned int>(personToModify.getBirthdate().getMonth() - 1 ) );

}

AddContact::~AddContact()
{
    delete ui;
}

void AddContact::loadBirthdayCombos() {
    QStringList months;
    int year = QDate::currentDate().year();

    for( unsigned int i = 1; i < 31; ++i ) {
        ui->comboDay->addItem( QString::number( i ) );
    }

    for ( int i = JENUARY_STR; i <= DECEMBER_STR; ++i ) {
        months << langManager.getText( i );
    }
    ui->comboMonth->addItems( months );
    for( int i = 1900; i <= year; ++i ) {
        ui->comboYear->addItem( QString::number( i ) );
    }
}

bool AddContact::isCorrectDate() {
    bool correctName;
    bool correctSurname;
    bool correctTelephone;
    bool correctEmail;

    correctName = ui->inputName->text() != "";
    correctSurname = ui->inputSurname->text() != "";
    correctTelephone = ui->inputTelephone->text() != "";
    correctEmail = ui->inputEmail->text() != "";
    return correctName && correctSurname && correctTelephone && correctEmail;
}

void AddContact::on_buttonBox_accepted()
{
    if ( isCorrectDate() ) {
        QStringList months;
        int monthValue = 1;
        int dayValue;
        int yearValue;
        for ( int i = JENUARY_STR; i <= DECEMBER_STR; ++i ) {
            months << langManager.getText( i );
        }
        for ( int i = 1; i <= 12; ++i ) {
            if( months[ i - 1 ] == ui->comboMonth->currentText() ) {
                monthValue = i;
            }
        }
        dayValue = ui->comboDay->currentText().toInt();
        yearValue = ui->comboYear->currentText().toInt();

        dataAccepted = true;
        AddedPerson.setName( ui->inputName->text().toStdString() );
        AddedPerson.setSurname( ui->inputSurname->text().toStdString() );
        AddedPerson.setBirthdate( Date( static_cast<unsigned int>(dayValue), static_cast<unsigned int>(monthValue), static_cast<unsigned int>(yearValue) ) );
        AddedPerson.setTelephone( ui->inputTelephone->text().toStdString() );
        AddedPerson.setEmail( ui->inputEmail->text().toStdString() );
        this->close();
    }

}

Person AddContact::getAddedPerson() {
    return AddedPerson;
}

void AddContact::on_buttonBox_rejected()
{
    dataAccepted = false;
    this->close();
}

bool AddContact::isDataAccepted() {
    return dataAccepted;
}

void AddContact::closeEvent(QCloseEvent *event) {
    event->accept();
}

void AddContact::setMainTexts() {
    ui->labelName->setText( langManager.getText( NAME_STR ) + ":" );
    ui->labelSurname->setText( langManager.getText( SURNAME_STR ) + ":" );
    ui->gruopBirthdate->setTitle( langManager.getText( BIRTHDATE_STR ) + ":" );
    ui->labelTelephone->setText( langManager.getText( TELEPHONE_STR ) + ":" );
    ui->labelEmail->setText( langManager.getText( EMAIL_STR ) + ":" );
    if ( editMode ) {
        this->setWindowTitle( langManager.getText( ADD_CONTACT_DIALOG_STR ) );
    } else {
        this->setWindowTitle( langManager.getText( EDIT_CONTACT_STR ) );
    }
}



