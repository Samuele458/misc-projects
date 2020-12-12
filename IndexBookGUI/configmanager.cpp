#include "configmanager.h"
#include <iostream>
ConfigManager::ConfigManager() : ConfigManager( QString( "config.dat" ) ) { }

ConfigManager::ConfigManager( QString filename ) {
    config_filename = filename;
    if ( fileExists( config_filename ) ) {
        QFile configFile( config_filename );
        if ( !configFile.open( QFile::Text | QFile::ReadOnly ) ) {
            qDebug( "Il file non è stato aperto in lettura" );
        }
        QTextStream in( &configFile );
        indexBookFilename = in.readLine();
        autosaveValue = in.readLine().toInt() == 1 ? true : false;

        language = in.readLine().toInt();




        configFile.close();
        qDebug( "Il file esiste" );
    } else {
        QFile configFile( config_filename );
        if ( !configFile.open( QFile::Text | QFile::WriteOnly ) ) {
            qDebug( "Il file non è stato aperto in scrittura" );
        }
        QTextStream out( &configFile );
        indexBookFilename = "IndexBook.dat";
        autosaveValue = true;
        language = 0;
        out << ( indexBookFilename + "\n1\n0" );
        configFile.flush();
        configFile.close();
        qDebug( "Il file NON esiste" );
    }
    QFile configFile( config_filename );

}

ConfigManager::ConfigManager( const ConfigManager& other ) {
    config_filename = other.config_filename;
    indexBookFilename = other.indexBookFilename;
    autosaveValue = other.autosaveValue;
    language = other.language;
}

ConfigManager& ConfigManager::operator=( const ConfigManager& other ) {
    config_filename = other.config_filename;
    indexBookFilename = other.indexBookFilename;
    autosaveValue = other.autosaveValue;
    language = other.language;
    return *this;
}

void ConfigManager::setFilename( QString filename ) {
    config_filename = filename;
}

QString ConfigManager::getFilename() const {
    return config_filename;
}

void ConfigManager::setIndexBookFilename( QString IndexBookFilenameStr ) {
    indexBookFilename = IndexBookFilenameStr;
}

QString ConfigManager::getIndexBookFilename() const {
    return indexBookFilename;
}

void ConfigManager::setAutosaveValue( bool value ) {
    autosaveValue = value;
}

bool ConfigManager::getAutosaveValue() const {
    return autosaveValue;
}

void ConfigManager::setLanguage( int languageValue ) {
    language = languageValue;
}

int ConfigManager::getLanguage() const {
    return language;
}

bool ConfigManager::fileExists(QString path) {
    QFileInfo check_file(path);
    // check if file exists and if yes: Is it really a file and no directory?
    if (check_file.exists() && check_file.isFile()) {
        return true;
    } else {
        return false;
    }
}

void ConfigManager::save() {
    QFile configFile( config_filename );
    if ( !configFile.open( QFile::Text | QFile::WriteOnly ) ) {
        qDebug( "Il file non è stato aperto in scrittura" );
    }
    QTextStream out( &configFile );

    out << ( indexBookFilename + "\n" + ( autosaveValue ? "1" : "0" ) + "\n" + QString::number( language ) );
    configFile.flush();
    configFile.close();
}
