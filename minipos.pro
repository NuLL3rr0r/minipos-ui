TEMPLATE = app


QT += core gui qml quick widgets
QT -= multimedia multimediawidgets network sql testlib webkit
android {
    QT += androidextras
}


android {
    DEFINES += STATIC_LINK_DEPENDENCIES
}
win32 {
    DEFINES += SHARED_LINK_DEPENDENCIES
}


QMAKE_CXXFLAGS += -std=c++1y
#INCLUDEPATH += $$PWD/dependencies/include
QMAKE_CFLAGS += -isystem $$PWD/dependencies/include
QMAKE_CXXFLAGS += -isystem $$PWD/dependencies/include


android {
    debug {
        LIBS += -L$$PWD/dependencies/lib/android_armv7/debug
    }
    release {
        LIBS += -L$$PWD/dependencies/lib/android_armv7/release
    }
}
win32 {
    debug {
        LIBS += -L$$PWD/dependencies/lib/mingw482_32/debug
    }
    release {
        LIBS += -L$$PWD/dependencies/lib/mingw482_32/release
    }
}
LIBS += -lboost_filesystem -lboost_system -lcppdb -lcppdb_sqlite3 -lsqlite3


HEADERS += \
    make_unique.hpp \
    Application.hpp \
    Database.hpp \
    Pool.hpp \
    UiEngine.hpp
SOURCES += \
    main.cpp \
    Application.cpp \
    Database.cpp \
    Pool.cpp \
    UiEngine.cpp
android {
    HEADERS += \
        Android.hpp
    SOURCES += \
        Android.cpp
}


RESOURCES += \
    deployment/resources/db.qrc \
    deployment/resources/fnt.qrc \
    deployment/resources/img.qrc \
    deployment/resources/ui.qrc


android {
    ANDROID_PACKAGE_SOURCE_DIR = $$PWD/deployment/android

    OTHER_FILES += \
        deployment/android/AndroidManifest.xml \
        deployment/android/res/drawable-hdpi/icon.png \
        deployment/android/res/drawable-ldpi/icon.png \
        deployment/android/res/drawable-mdpi/icon.png \
        deployment/android/res/values/strings.xml
}


# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

