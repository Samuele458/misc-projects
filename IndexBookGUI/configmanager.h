#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H
#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileInfo>
#include "languagesmanager.h"

class ConfigManager
{
    public:

        ConfigManager();
        ConfigManager( QString filename );
        ConfigManager( const ConfigManager& other );
        ConfigManager& operator=( const ConfigManager& other );


        void setFilename( QString filename );
        QString getFilename() const;

        void setIndexBookFilename( QString IndexBookFilenameStr);
        QString getIndexBookFilename() const;

        void setAutosaveValue( bool value );
        bool getAutosaveValue() const;

        void setLanguage( int languageValue );
        int getLanguage() const;

        void save();

    private:
        QString config_filename;
        QString indexBookFilename;
        bool autosaveValue;
        int language;

        bool fileExists(QString path);

};

#endif // CONFIGMANAGER_H
