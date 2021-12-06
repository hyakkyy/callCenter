QT += testlib
QT += testlib
QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += qt warn_on depend_includepath testcase
CONFIG += c++17

TEMPLATE = app

SOURCES +=  ../../testlib/testlib.cpp \
        tst_usersadding.cpp \
        ../../lib/register_user.cpp \
        ../../lib/user.cpp


HEADERS += \
        ../../testlib/testlib.hpp \
        ../../lib/register_user.hpp \
        ../../lib/user.hpp

FORMS += \
        ../../lib/register_user.ui \
