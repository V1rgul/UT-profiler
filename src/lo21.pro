#-------------------------------------------------
#
# Project created by QtCreator 2014-05-17T03:39:19
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lo21
TEMPLATE = app


SOURCES += main.cpp\
    view/mainwindow.cpp \
    model/etudiant.cpp \
    model/formation.cpp \
    model/semestre.cpp \
    model/uvEtudiant.cpp \
    model/catalogue.cpp \
    model/uv.cpp \
    view/qformation.cpp \
    view/qsemestre.cpp

HEADERS  += view/mainwindow.h \
    model/etudiant.h \
    model/formation.h \
    model/semestre.h \
    model/uvEtudiant.h \
    model/catalogue.h \
    model/uv.h \
    model/semestreInvalideErreur.h \
    model/xmlConvertible.h \
    view/qformation.h \
    view/qsemestre.h

FORMS    += view/mainwindow.ui \
    view/qsemestre.ui \
    view/qformation.ui

INCLUDEPATH += view

RESOURCES     = ressources.qrc \
    ressources.qrc
