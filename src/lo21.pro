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
    model/etudiant.cpp \
    model/formation.cpp \
    model/semestre.cpp \
    model/uvEtudiant.cpp \
    model/catalogue.cpp \
    model/uv.cpp \
    model/formationHorsUtc.cpp \
    model/formationUtc.cpp \
    view/mainwindow.cpp \
    view/qformation.cpp \
    view/qsemestre.cpp \
    view/quserdialog.cpp \
    view/qsemestredialog.cpp \
    controller/mainwindowcontroller.cpp \
    controller/formationcontroller.cpp \


HEADERS  += \
    model/etudiant.h \
    model/formation.h \
    model/semestre.h \
    model/uvEtudiant.h \
    model/catalogue.h \
    model/uv.h \
    model/semestreInvalideErreur.h \
    model/xmlConvertible.h \
    model/formationHorsUtc.h \
    model/formationUtc.h \
    view/mainwindow.h \
    view/qformation.h \
    view/qsemestre.h \    
    view/quserdialog.h \    
    view/qsemestredialog.h \
    controller/mainwindowcontroller.h \
    controller/formationcontroller.h

FORMS    += view/mainwindow.ui \
    view/qsemestre.ui \
    view/qformation.ui \
    view/quserdialog.ui \
    view/qsemestredialog.ui

INCLUDEPATH += view

RESOURCES     = ressources.qrc \
    ressources.qrc
