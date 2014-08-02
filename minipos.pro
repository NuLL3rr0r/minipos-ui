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
QMAKE_CXXFLAGS += -Wall -Wextra -pedantic
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
    Pos.hpp \
    UiEngine.hpp
SOURCES += \
    main.cpp \
    Application.cpp \
    Database.cpp \
    Pool.cpp \
    Pos.cpp \
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
        deployment/android/libs/n38_1.jar \
        deployment/android/res/drawable-hdpi/icon.png \
        deployment/android/res/drawable-ldpi/icon.png \
        deployment/android/res/drawable-mdpi/icon.png \
        deployment/android/res/values/strings.xml \
        deployment/android/src/com/rahpooyanco/minipos/Android.java
}

lupdate_only {
    SOURCES += \
        $$PWD/deployment/resources/ui/main.qml
}


#################
# Automatically generating .qm language files and adding them to resources
#################

# var, prepend, append
defineReplace(prependAll) {
    for(a,$$1):result += $$2$${a}$$3
    return($$result)
}

# Supported languages
LANGUAGES = en fa

# Available translations
TRANSLATIONS = $$prependAll(LANGUAGES, $$PWD/translations/, .ts)

# Used to embed the qm files in resources
TRANSLATIONS_FILES =

# run LRELEASE to generate the qm files
qtPrepareTool(LRELEASE, lrelease)
for(tsfile, TRANSLATIONS) {
    qmfile = $$shadowed($$tsfile)
    qmfile ~= s,\\.ts$,.qm,
    qmdir = $$dirname(qmfile)
    !exists($$qmdir) {
        mkpath($$qmdir)|error("Aborting.")
    }
    command = $$LRELEASE -removeidentical $$tsfile -qm  $$qmfile
    system($$command)|error("Failed to run: $$command")
    TRANSLATIONS_FILES += $$qmfile
}

# Create the resource file
GENERATED_RESOURCE_FILE = $$OUT_PWD/translations.qrc

RESOURCE_CONTENT = \
    "<RCC>" \
    "<qresource>"

for(translationfile, TRANSLATIONS_FILES) {
    relativepath_out = $$relative_path($$translationfile, $$OUT_PWD)
    RESOURCE_CONTENT += "<file alias=\"$$relativepath_out\">$$relativepath_out</file>"
}

RESOURCE_CONTENT += \
    "</qresource>" \
    "</RCC>"

write_file($$GENERATED_RESOURCE_FILE, RESOURCE_CONTENT)|error("Aborting.")

RESOURCES += $$GENERATED_RESOURCE_FILE

#################
### End of  # Automatically generating .qm language files and adding them to resources
#################


# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

