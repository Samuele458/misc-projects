#ifndef ADDCONTACT_H
#define ADDCONTACT_H

#include <QDialog>
#include <QDate>
#include <QCloseEvent>
#include "index_book.h"
#include "languagesmanager.h"

namespace Ui {
class AddContact;
}

class AddContact : public QDialog
{
    Q_OBJECT

public:
    explicit AddContact(QWidget *parent = nullptr, LanguagesManager lManager = LanguagesManager() );
    explicit AddContact(Person personToModify, QWidget *parent = nullptr, LanguagesManager lManager = LanguagesManager());
    ~AddContact();
    bool isDataAccepted();
    Person getAddedPerson();
    void setMainTexts();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    void loadBirthdayCombos();
    bool isCorrectDate();
    Person AddedPerson;
    bool dataAccepted;
    Ui::AddContact *ui;
    bool editMode;
    LanguagesManager langManager;
    void closeEvent (QCloseEvent *event);
};

#endif // ADDCONTACT_H
