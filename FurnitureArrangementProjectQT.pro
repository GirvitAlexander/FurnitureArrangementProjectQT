QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEFINES += PRO_FILE_PWD=$$sprintf("\"\\\"%1\\\"\"", $$_PRO_FILE_PWD_)

SOURCES += \
    addfurnitureroomdialog.cpp \
    changeroomfurnituredialog.cpp \
    changewallfurnituredialog.cpp \
    conditionwidget.cpp \
    furniture.cpp \
    graphicwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    parametrwidget.cpp \
    room.cpp

HEADERS += \
    addfurnitureroomdialog.h \
    changeroomfurnituredialog.h \
    changewallfurnituredialog.h \
    conditionwidget.h \
    furniture.h \
    graphicwidget.h \
    mainwindow.h \
    parametrwidget.h \
    room.h \
    typesfurnitures.h

FORMS += \
    addfurnitureroomdialog.ui \
    changeroomfurnituredialog.ui \
    changewallfurnituredialog.ui \
    conditionwidget.ui \
    graphicwidget.ui \
    mainwindow.ui \
    parametrwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


OTHER_FILES += Save/start.txt \
Save/example.txt
