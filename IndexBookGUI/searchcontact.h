#ifndef SEARCHCONTACT_H
#define SEARCHCONTACT_H

#include <QDialog>
#include "languagesmanager.h"
#include "index_book.h"

enum PosizionValue : int {
    NOT_FOUND = -1,
    REJECTED = -2
};

namespace Ui {
class SearchContact;
}

class SearchContact : public QDialog
{
    Q_OBJECT

public:
    explicit SearchContact( IndexBook book, QWidget *parent = nullptr, LanguagesManager lManager = LanguagesManager() );
    ~SearchContact();
    void setMainTexts();
    int getContactPosition();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::SearchContact *ui;
    LanguagesManager langManger;
    int position;
    IndexBook bookToAnalyze;
};

#endif // SEARCHCONTACT_H
