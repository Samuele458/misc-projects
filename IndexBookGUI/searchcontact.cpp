#include "searchcontact.h"
#include "ui_searchcontact.h"

SearchContact::SearchContact( IndexBook book, QWidget *parent, LanguagesManager lManager ) :
    QDialog(parent),
    ui(new Ui::SearchContact)
{
    ui->setupUi(this);
    langManger = lManager;
    position = REJECTED;
    bookToAnalyze = book;
    setMainTexts();
}

SearchContact::~SearchContact()
{
    delete ui;
}

void SearchContact::on_buttonBox_accepted()
{
    position = bookToAnalyze.searchPerson( ui->inputName->text().toStdString(), ui->inputSurname->text().toStdString() );
    this->close();
}

void SearchContact::on_buttonBox_rejected()
{
    position = REJECTED;
    this->close();
}

void SearchContact::setMainTexts() {
    this->setWindowTitle( langManger.getText( SEARCH_CONTACT_STR ) );
    ui->labelName->setText( langManger.getText( NAME_STR ) + ":" );
    ui->labelSurname->setText( langManger.getText( SURNAME_STR ) + ":" );
}

int SearchContact::getContactPosition() {
    return position;
}
