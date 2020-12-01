
QT += core gui widgets sql
TARGET = doogie
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += c++11
CONFIG += link_pkgconfig
PKGCONFIG += gtk+-2.0
# We want a console window for logs during debug
debug:CONFIG += console

# Keep all sources and headers in alphabetical order

SOURCES += \
    browser_setting.cc \
    bubble.cc \
    main.cc \
    profile.cc \
    sql.cc \
    util.cc \
    gtk_utils.cpp

HEADERS += \
    browser_setting.h \
    bubble.h \
    profile.h \
    sql.h \
    util.h \
    gtk_utils.h

RESOURCES += \
    doogie.qrc

release:PROFILE = Release
debug:PROFILE = Debug

win32 {
    LIBS += -luser32 -lcrypt32 -lcryptui

    SOURCES += \
        util_win.cc

    # Chromium reads the manifest, needs a specific one
    # See http://magpcss.org/ceforum/viewtopic.php?f=6&t=14721
    CONFIG -= embed_manifest_exe
    RC_FILE = doogie.rc

    # We have to ignore this compiler warning because MSVC
    #  complains about > 255 type name lengths in debug which
    #  we don't care about.
    QMAKE_CXXFLAGS += /wd4503
}

unix {
    LIBS += -lX11
    QMAKE_RPATHDIR += $ORIGIN
    #QMAKE_CXXFLAGS += -Werror

    SOURCES += \
        util_linux.cc

    release:MOC_DIR = release
    release:OBJECTS_DIR = release
    release:DESTDIR = release
    debug:MOC_DIR = debug
    debug:OBJECTS_DIR = debug
    debug:DESTDIR = debug
}

INCLUDEPATH += $$(CEF_DIR)


# include cef folder
include(cef/cef.pri)
