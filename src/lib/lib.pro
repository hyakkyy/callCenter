QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    call.cpp \
    callhistory.cpp \
    clientmainwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    startcall.cpp \
    user.cpp

HEADERS += \
    call.hpp \
    callhistory.hpp \
    clientmainwindow.hpp \
    mainwindow.hpp \
    startcall.hpp \
    user.hpp

FORMS += \
    authform.ui \
    callhistory.ui \
    clientmainwindow.ui \
    mainwindow.ui \
    startcall.ui

CONFIG += c++17

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
