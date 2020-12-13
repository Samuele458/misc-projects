#-------------------------------------------------
#
# Project created by QtCreator 2019-02-15T22:18:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IndexBookGUI
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    ArrayUtilities/random.cpp \
    date.cpp \
    index_book.cpp \
    person.cpp \
    string_processing.cpp \
    addcontact.cpp \
    configdialog.cpp \
    configmanager.cpp \
    languagesmanager.cpp \
    searchcontact.cpp

HEADERS += \
        mainwindow.h \
    ArrayUtilities/array.h \
    ArrayUtilities/binary_search.h \
    ArrayUtilities/quick_sort.h \
    ArrayUtilities/random.h \
    ArrayUtilities/searching.h \
    ArrayUtilities/sorting.h \
    array_utilities.h \
    date.h \
    index_book.h \
    person.h \
    string_processing.h \
    addcontact.h \
    configdialog.h \
    configmanager.h \
    languagesmanager.h \
    searchcontact.h

FORMS += \
        mainwindow.ui \
    addcontact.ui \
    configdialog.ui \
    searchcontact.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    IndexBook.dat

RESOURCES += \
    resource.qrc
