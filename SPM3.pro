QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 console

QT += sql

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    accueil_gestionnaire.cpp \
    afficher_client.cpp \
    afficher_compte.cpp \
    ajout_client.cpp \
    banqueappli.cpp \
    creer_compte.cpp \
    creer_gestionnaire.cpp \
    main.cpp \
    banque.cpp\
    client.cpp\
    comptebancaire.cpp\
    gestionnairebanque.cpp\
    sauver_charger.cpp \
    sup_client.cpp \
    supp_compte.cpp \
    transaction.cpp\

HEADERS += \
    accueil_gestionnaire.h \
    afficher_client.h \
    afficher_compte.h \
    ajout_client.h \
    banque.h\
    banqueappli.h \
    client.h\
    comptebancaire.h\
    creer_compte.h \
    creer_gestionnaire.h \
    gestionnairebanque.h\
    sauver_charger.h \
    sup_client.h \
    supp_compte.h \
    transaction.h\
    periode.h\
    typetransaction.h\

FORMS += \
    accueil_gestionnaire.ui \
    afficher_client.ui \
    afficher_compte.ui \
    ajout_client.ui \
    banque.ui \
    creer_compte.ui \
    creer_gestionnaire.ui \
    sauver_charger.ui \
    sup_client.ui \
    supp_compte.ui

TRANSLATIONS += \
    SPM3_fr_GA.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Setting the custom target for Doxygen documentation
doxygen.target = doc
doxygen.commands = doxygen Doxyfile
QMAKE_EXTRA_TARGETS += doxygen
PRE_TARGETDEPS += doc

# Definition of the dependency on the Doxygen documentation target
doc.depends = doxygen

