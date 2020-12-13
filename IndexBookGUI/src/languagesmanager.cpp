#include "languagesmanager.h"

LanguagesManager::LanguagesManager() : LanguagesManager( ENGLISH ) { }

LanguagesManager::LanguagesManager( int languageValue )
{
    language = languageValue;
    loadStrings();
}

LanguagesManager::LanguagesManager( const LanguagesManager& other ) {
    language = other.language;
    languageStrings = other.languageStrings;
}

LanguagesManager& LanguagesManager::operator=( const LanguagesManager& other ) {
    language = other.language;
    languageStrings = other.languageStrings;
    return *this;
}

void LanguagesManager::setLanguage( int languageValue ) {
    language = languageValue;
    loadStrings();
}

int LanguagesManager::getLanguage() const {
    return language;
}

QString LanguagesManager::getText( int textVal ) const {
    return languageStrings[ textVal ];
}

void LanguagesManager::loadStrings() {
    languageStrings.clear();
    QString languageFilename;
    switch ( language ) {
        case ENGLISH:
            languageFilename = ":/Languages/english.dat";
            qDebug( "LINGUA INGLESE" );
            break;
        case ITALIAN:
            languageFilename = ":/Languages/italian.dat";
            qDebug( "LINGUA ITALIANA" );

            break;
    }
    QFile languageFile( languageFilename );
    if ( !languageFile.open( QFile::Text | QFile::ReadOnly ) ) {
        qDebug( "FILE INGLESE NON APERTO" );
    }
    QTextStream in( &languageFile );
    while( !in.atEnd() ) {
        languageStrings << in.readLine();
    }
}
