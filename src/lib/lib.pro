QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    call.cpp \
    callhistory.cpp \
    clientmainwindow.cpp \
    edit_user.cpp \
    main.cpp \
    mainwindow.cpp \
    managermainwindow.cpp \
    register_user.cpp \
    startcall.cpp \
    user.cpp \
    users_table.cpp

HEADERS += \
    call.hpp \
    callhistory.hpp \
    clientmainwindow.hpp \
    config.hpp \
    edit_user.hpp \
    mainwindow.hpp \
    managermainwindow.hpp \
    register_user.hpp \
    startcall.hpp \
    user.hpp \
    users_table.hpp

FORMS += \
    authform.ui \
    callhistory.ui \
    clientmainwindow.ui \
    edit_user.ui \
    mainwindow.ui \
    managermainwindow.ui \
    register_user.ui \
    startcall.ui \
    users_table.ui

CONFIG += c++11
