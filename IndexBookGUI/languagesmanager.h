#ifndef LANGUAGESMANAGER_H
#define LANGUAGESMANAGER_H
#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextStream>

enum LanguagesId : int {
    ENGLISH = 0,
    ITALIAN
};

enum StringsId : int {
    NAME_STR = 0,
    SURNAME_STR,
    BIRTHDATE_STR,
    TELEPHONE_STR,
    EMAIL_STR,
    REMOVE_STR,
    EDIT_STR,
    CONTACT_LOADED_STR,
    CONTACTS_LOADED_STR,
    FILE_MENU_STR,
    EDIT_MENU_STR,
    SAVE_STR,
    SAVE_AS_STR,
    LOAD_FROM_STR,
    CLOSE_STR,
    NEW_CONTACT_STR,
    EDIT_CONTACT_STR,
    DELETE_CONTACT_STR,
    DELETE_ALL_STR,
    OPTIONS_STR,
    OPTIONS_TOOLTIP_STR,
    SAVE_FILE_TOOLTIP_STR,
    EDIT_CONTACT_TOOLTIP_STR,
    DELETE_CONTACT_TOOLTIP_STR,
    ADD_CONTACT_TOOLTIP_STR,
    JENUARY_STR,
    FEBRUARY_STR,
    MARCH_STR,
    APRIL_STR,
    MAY_STR,
    JUNE_STR,
    JULY_STR,
    AUGUST_STR,
    SEPTEMBER_STR,
    OCTOBER_STR,
    NOVEMBER_STR,
    DECEMBER_STR,
    LANGUAGE_STR,
    SELECT_LANGUAGE_STR,
    FILE_CONFIG_STR,
    STANDARD_FILE_TO_LOAD_STR,
    AUTOSAVE_STR,
    MAINWINDOW_TITLE_STR,
    CONFIG_DIALOG_TITLE_STR,
    ADD_CONTACT_DIALOG_STR,
    SORT_BY_STR,
    SORTING_ORDER_STR,
    INCREASING_ORDER_STR,
    DECREASING_ORDER_STR,
    SEARCH_CONTACT_TOOLTIP,
    SEARCH_CONTACT_STR,
    STRINGS_COUNTER

};

class LanguagesManager
{
    public:
        LanguagesManager();
        LanguagesManager( int languageValue );
        LanguagesManager( const LanguagesManager& other );
        LanguagesManager& operator=( const LanguagesManager& other );
        void setLanguage( int languageValue );
        int getLanguage() const;
        QString getText( int textVal ) const;

    private:
        void loadStrings();

        int language;
        QStringList languageStrings;
};

#endif // LANGUAGESMANAGER_H
