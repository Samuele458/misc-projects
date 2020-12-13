#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "index_book.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    lManager = LanguagesManager( manager.getLanguage() );
    manager = ConfigManager();

    QStringList HeadersTitles;
    HeadersTitles << "Name" << "Surname" << "Birthdate" << "Telephone" << "Email" << "Remove" << "Edit";
    ui->IndexBookTable->setColumnCount( 7 );
    ui->IndexBookTable->setHorizontalHeaderLabels( HeadersTitles );
    book = IndexBook( manager.getIndexBookFilename().toStdString() );

    loadAllContacts( book );
    statusBarRefresh();

    indexSortBy = NAME;
    indexSortingOrder = 0;
    setMainTexts();


}

MainWindow::~MainWindow()
{
    if ( manager.getAutosaveValue() )
        book.save( manager.getIndexBookFilename().toStdString() );
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    AddContact j( this, lManager );
    j.show();
    j.exec();
    if ( j.isDataAccepted() ) {
        IndexBookTableAddPerson( j.getAddedPerson() );
        book.addPerson( j.getAddedPerson() );
        statusBarRefresh();
    }
}

void MainWindow::IndexBookTableAddPerson( Person personToAdd, int row ) {
    int row_c;
    if ( row == -1 ) {
        ui->IndexBookTable->insertRow( ui->IndexBookTable->rowCount() );
        row_c = ui->IndexBookTable->rowCount() - 1;

    } else {
        row_c = row;
    }

    ui->IndexBookTable->setItem( row_c, NAME_ID, new QTableWidgetItem( QString::fromStdString( personToAdd.getName() ) ) );
    ui->IndexBookTable->setItem( row_c, SURNAME_ID, new QTableWidgetItem( QString::fromStdString( personToAdd.getSurname() ) ) );
    ui->IndexBookTable->setItem( row_c, BIRTHDATE_ID, new QTableWidgetItem( QString::fromStdString( personToAdd.getBirthdate().getStringDate() ) ) );
    ui->IndexBookTable->setItem( row_c, TELEPHONE_ID, new QTableWidgetItem( QString::fromStdString( personToAdd.getTelephone() ) ) );
    ui->IndexBookTable->setItem( row_c, EMAIL_ID, new QTableWidgetItem( QString::fromStdString( personToAdd.getEmail() ) ) );
    QTableWidgetItem *icon_remove = new QTableWidgetItem;
    QIcon icon_r(":/icons/delete.png");
    icon_remove->setIcon(icon_r);
    ui->IndexBookTable->setItem( row_c, REMOVE_ID, icon_remove );
    QTableWidgetItem *icon_edit = new QTableWidgetItem;
    QIcon icon_e(":/icons/edit.png");
    icon_edit->setIcon(icon_e);
    ui->IndexBookTable->setItem( row_c, EDIT_ID, icon_edit );

}

void MainWindow::loadAllContacts( IndexBook book ) {
    for ( int i = ui->IndexBookTable->rowCount(); i >= 0; --i ) {
        ui->IndexBookTable->removeRow( i );
    }
    for ( unsigned int i = 0; i < book.getPeopleNumber(); ++i ) {
        IndexBookTableAddPerson( book.getPerson( i ) );
    }
}

void MainWindow::on_IndexBookTable_cellActivated(int row, int column)
{
    if ( column == REMOVE_ID ) {
        removePersonFromTable( row );
    } else if ( column == EDIT_ID ){
        editPersonFromTable( row );
    }
}

void MainWindow::statusBarRefresh() {
    QString StatusBarMsg;
    StatusBarMsg = QString::number( book.getPeopleNumber() ) + " " + ( book.getPeopleNumber() == 1 ? lManager.getText( CONTACT_LOADED_STR ) : lManager.getText( CONTACTS_LOADED_STR) );
    ui->statusBar->showMessage( StatusBarMsg );
}

void MainWindow::on_actionClose_triggered()
{
    this->close();
}


int MainWindow::checkedRow() {
    for ( int i = 0; i < ui->IndexBookTable->rowCount(); ++i ) {
        if( ui->IndexBookTable->item( i, 0 )->isSelected() ) {
            return i;
        }
    }
    return -1;
}

void MainWindow::on_actionDelete_contact_triggered()
{
    int rowToRemove;
    rowToRemove = checkedRow();
    if ( rowToRemove != -1 ) {
        removePersonFromTable( rowToRemove );
    }
}

void MainWindow::removePersonFromTable( int position ) {
    ui->IndexBookTable->removeRow( position );
    book.removePerson( static_cast<unsigned int>( position ) );
}

void MainWindow::editPersonFromTable(int position) {
    AddContact z( book.getPerson( static_cast<unsigned int> ( position ) ), this, lManager );
    z.show();
    z.exec();
    if ( z.isDataAccepted() ) {
        IndexBookTableAddPerson( z.getAddedPerson(), position );
        book.addPerson( z.getAddedPerson(), position );

        statusBarRefresh();
    }
}

void MainWindow::on_actionEdit_contact_triggered()
{
    int rowToEdit;
    rowToEdit = checkedRow();
    if ( rowToEdit != -1 ) {
        editPersonFromTable( rowToEdit );
    }
}

void MainWindow::on_actionNew_contact_triggered()
{
    on_pushButton_clicked();
}

void MainWindow::on_actionSave_triggered()
{
    book.save( manager.getIndexBookFilename().toStdString() );
}

void MainWindow::on_actionSave_as_triggered()
{
    QString dir = QFileDialog::getSaveFileName( this, "Save as" );
    book.save( dir.toStdString() );
}

void MainWindow::on_actionLoad_from_triggered()
{
    QFileDialog* chooseFile = new QFileDialog( this, "Choose a file", QDir::currentPath(), "*.dat" );
    chooseFile->exec();
    QStringList fileList = chooseFile->selectedFiles();
    if ( fileList.count() > 0 ) {
        book = IndexBook( fileList[0].toStdString() );
    }
    loadAllContacts( book );
}


void MainWindow::on_actionDelete_all_triggered()
{
    for ( int i = 0; i < ui->IndexBookTable->rowCount(); ++i ) {
        ui->IndexBookTable->removeRow( i );
        book.removePerson( static_cast<unsigned int>( i ) );
    }
    loadAllContacts( book );
}



void MainWindow::on_toolButton_clicked()
{
    //ConfigManager a;


    /*QFile configFile( "/home/samuele/Scrivania/config.dat" );

    if ( !configFile.open( QFile::WriteOnly | QFile::Text | QFile::Append ) ) {
        QMessageBox::warning(this, "ERROR", "file not open" );
    }
    QTextStream out( &configFile );
    QString a = "CIao\n";
    out << a;
    configFile.flush();
    configFile.close(); */

    ConfigDialog k( &manager, lManager, this );

    k.show();
    k.exec();
    lManager.setLanguage( manager.getLanguage() );
    setMainTexts();
    statusBarRefresh();

}

void MainWindow::on_actionOptions_triggered()
{
    on_toolButton_clicked();
}

void MainWindow::setMainTexts() {

    QStringList HorizontalHeaderTable;
    for ( int i = NAME_STR; i <= EDIT_STR; ++i ) {
        HorizontalHeaderTable << lManager.getText( i );
    }

    //HorizontalHeaderTable << lManager.getText( NAME_STR ) << lManager.getText( SURNAME_STR ) << lManager.getText( BIRTHDATE_STR ) << lManager.getText( TELEPHONE_STR ) << lManager.getText( EMAIL_STR ) << lManager.getText( REMOVE_STR ) << lManager.getText( EDIT_STR );
    ui->IndexBookTable->setHorizontalHeaderLabels( HorizontalHeaderTable );
    ui->menuFile->setTitle( lManager.getText( FILE_MENU_STR ) );
    ui->menuEdit->setTitle( lManager.getText( EDIT_MENU_STR ) );
    ui->actionSave->setText( lManager.getText( SAVE_STR ) );
    ui->actionSave_as->setText( lManager.getText( SAVE_AS_STR ) );
    ui->actionLoad_from->setText( lManager.getText( LOAD_FROM_STR ) );
    ui->actionClose->setText( lManager.getText( CLOSE_STR ) );
    ui->actionNew_contact->setText( lManager.getText( NEW_CONTACT_STR ) );
    ui->actionEdit_contact->setText( lManager.getText( EDIT_CONTACT_STR ) );
    ui->actionDelete_contact->setText( lManager.getText( DELETE_CONTACT_STR ) );
    ui->actionDelete_all->setText( lManager.getText( DELETE_ALL_STR ) );
    ui->actionOptions->setText( lManager.getText( OPTIONS_STR ) );
    ui->actionSave->setToolTip( lManager.getText( SAVE_FILE_TOOLTIP_STR ) );
    ui->actionOptions->setToolTip( lManager.getText( OPTIONS_TOOLTIP_STR ) );
    ui->actionEdit_contact->setToolTip( lManager.getText( EDIT_CONTACT_TOOLTIP_STR ) );
    ui->actionDelete_contact->setToolTip( lManager.getText( DELETE_CONTACT_TOOLTIP_STR ) );
    ui->actionNew_contact->setToolTip( lManager.getText( ADD_CONTACT_TOOLTIP_STR ) );

    ui->pushButton->setText( lManager.getText( NEW_CONTACT_STR ) );
    ui->pushButton->setToolTip( lManager.getText( ADD_CONTACT_TOOLTIP_STR ) );
    this->setWindowTitle( lManager.getText( MAINWINDOW_TITLE_STR ) );

    ui->labelSortingBy->setText( lManager.getText( SORT_BY_STR ) );
    ui->labelSortingOrder->setText( lManager.getText( SORTING_ORDER_STR ) );
    ui->comboSortingOrder->clear();
    ui->comboSortingOrder->addItem( lManager.getText( INCREASING_ORDER_STR ) );
    ui->comboSortingOrder->addItem( lManager.getText( DECREASING_ORDER_STR ) );
    ui->comboSortBy->clear();

    for ( int i = NAME_STR; i <= EMAIL_STR; ++i ) {
        ui->comboSortBy->addItem( lManager.getText( i ) );

    }

}

void MainWindow::sortIndexBookTable( int sort_by, int sortingOrder ) {
    Person::ParameterToCompare = static_cast<comparisonParameter>( sort_by );
    book.sortIndex( sortingOrder == 0 ? true : false );
    loadAllContacts( book );
}

void MainWindow::on_comboSortBy_activated(int index)
{
    indexSortBy = index;
    sortIndexBookTable( indexSortBy, indexSortingOrder );
}

void MainWindow::on_comboSortingOrder_activated(int index)
{
    indexSortingOrder = index;
    sortIndexBookTable( indexSortBy, indexSortingOrder );
}

void MainWindow::on_actionSearch_triggered()
{
    SearchContact k( book, this, lManager );
    k.show();
    k.exec();
    int position = k.getContactPosition();
    if ( position > NOT_FOUND ) {
        //sortIndexBookTable( SURNAME, 0 );
        ui->IndexBookTable->selectRow( position );
        ui->statusBar->showMessage( QString::number( position ) );
    }
    //ui->IndexBookTable->selectRow( 2 );
}
