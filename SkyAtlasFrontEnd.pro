QT += widgets

TEMPLATE = app
TARGET = SkyAtlas

INCLUDEPATH += /Users/adamfrench/boost/include/

LIBS += -L /Users/adamfrench/Library/Developer/Xcode/DerivedData/SkyAtlas-gocdgtuzxaizbkfwiykjmqbbydws/Build/Products/Debug/ -l SkyAtlasStaticLibrary

HEADERS = SkyAtlasFrontEnd/*.h \
SkyAtlas/Model/*.h \
SkyAtlas/View/*.h

SOURCES = SkyAtlasFrontEnd/SkyAtlasFrontEnd.cpp \
SkyAtlasFrontEnd/MainWindow.cpp \
SkyAtlasFrontEnd/SkyWidget.cpp

