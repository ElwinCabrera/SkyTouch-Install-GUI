#-------------------------------------------------
#
# Project created by QtCreator 2019-07-15T15:15:34
#
#-------------------------------------------------

QT       += core gui

QT      += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SkyTouchPOSSetup
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

#RC_FILE = SkyTouchPOSSetup.rc
RC_ICONS = icon2.ico

SMTP_LIBRARY_LOCATION = $$PWD/../build-SMTPEmail-Desktop-Release

win32:CONFIG(release, debug|release): LIBS += -L$$SMTP_LIBRARY_LOCATION/release/ -lSMTPEmail
else:win32:CONFIG(debug, debug|release): LIBS += -L$$SMTP_LIBRARY_LOCATION/debug/ -lSMTPEmail
else:unix: LIBS += -L$$SMTP_LIBRARY_LOCATION -lSMTPEmail

INCLUDEPATH += $$SMTP_LIBRARY_LOCATION
DEPENDPATH += $$SMTP_LIBRARY_LOCATION


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    pages.cpp \
    network.cpp \
    installconfirmation.cpp \
    registryhandler.cpp \
    global.cpp \
    softwareinfo.cpp \
    usereditlinks.cpp \
    usereditregistry.cpp \
    optionsmenu.cpp \
    addfilesmenu.cpp \
    reportbugsmenu.cpp

HEADERS += \
        mainwindow.h \
    pages.h \
    network.h \
    installconfirmation.h \
    global.h \
    registryhandler.h \
    softwareinfo.h \
    usereditlinks.h \
    usereditregistry.h \
    optionsmenu.h \
    addfilesmenu.h \
    reportbugsmenu.h

FORMS +=

RESOURCES += \
    recources.qrc
