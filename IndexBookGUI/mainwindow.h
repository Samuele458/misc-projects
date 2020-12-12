#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QStringList>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QComboBox>

#include "addcontact.h"
#include "configdialog.h"
#include "configmanager.h"
#include "languagesmanager.h"
#include "searchcontact.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    enum columnId : int {
        NAME_ID = 0, SURNAME_ID, BIRTHDATE_ID, TELEPHONE_ID, EMAIL_ID, REMOVE_ID, EDIT_ID
    };

    void setMainTexts();


private slots:
    void on_pushButton_clicked();

    void on_IndexBookTable_cellActivated(int row, int column);

    void on_actionClose_triggered();

    void on_actionDelete_contact_triggered();

    void on_actionEdit_contact_triggered();

    void on_actionNew_contact_triggered();

    void on_actionSave_triggered();

    void on_actionSave_as_triggered();

    void on_actionLoad_from_triggered();

    void on_actionDelete_all_triggered();

    void on_toolButton_clicked();

    void on_actionOptions_triggered();

    void on_comboSortBy_activated(int index);

    void on_comboSortingOrder_activated(int index);

    void on_actionSearch_triggered();

private:
    void IndexBookTableAddPerson( Person personToAdd, int row = -1 );
    void loadAllContacts( IndexBook book );
    void statusBarRefresh();
    IndexBook book;
    void removePersonFromTable( int position );
    void editPersonFromTable( int position );
    int checkedRow();
    void sortIndexBookTable( int sort_by, int sortingOrder );
    Ui::MainWindow *ui;
    ConfigManager manager;
    LanguagesManager lManager;
    int indexSortBy;
    int indexSortingOrder;
};

#endif // MAINWINDOW_H
