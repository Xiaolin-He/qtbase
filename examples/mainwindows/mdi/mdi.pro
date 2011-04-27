HEADERS       = mainwindow.h \
                mdichild.h
SOURCES       = main.cpp \
                mainwindow.cpp \
                mdichild.cpp
RESOURCES     = mdi.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/qtbase/mainwindows/mdi
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS mdi.pro images
sources.path = $$[QT_INSTALL_EXAMPLES]/qtbase/mainwindows/mdi
INSTALLS += target sources

symbian: include($$QT_SOURCE_TREE/examples/symbianpkgrules.pri)
