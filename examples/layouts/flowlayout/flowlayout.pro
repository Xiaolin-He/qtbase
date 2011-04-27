HEADERS     = flowlayout.h \
              window.h
SOURCES     = flowlayout.cpp \
              main.cpp \
              window.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/qtbase/layouts/flowlayout
sources.files = $$SOURCES $$HEADERS *.pro
sources.path = $$[QT_INSTALL_EXAMPLES]/qtbase/layouts/flowlayout
INSTALLS += target sources

symbian: include($$QT_SOURCE_TREE/examples/symbianpkgrules.pri)
