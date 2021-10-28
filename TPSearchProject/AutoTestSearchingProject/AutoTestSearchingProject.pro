QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_autotest.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../LibrarySearchingProject/release/ -lLibrarySearchingProject
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../LibrarySearchingProject/debug/ -lLibrarySearchingProject
else:unix: LIBS += -L$$OUT_PWD/../LibrarySearchingProject/ -lLibrarySearchingProject

INCLUDEPATH += $$PWD/../LibrarySearchingProject
DEPENDPATH += $$PWD/../LibrarySearchingProject
