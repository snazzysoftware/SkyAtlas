QT += widgets

TEMPLATE = app
TARGET = SkyAtlas

INCLUDEPATH += /Users/adamfrench/boost/include/

HEADERS = SkyAtlasFrontEnd/*.h \
SkyAtlas/Model/*.h \
SkyAtlas/View/*.h

SOURCES = SkyAtlasFrontEnd/SkyAtlasFrontEnd.cpp \
SkyAtlasFrontEnd/MainWindow.cpp \
SkyAtlasFrontEnd/SkyWidget.cpp \
SkyAtlas/Model/Constellation.cpp \
SkyAtlas/Model/Grids.cpp \
SkyAtlas/Model/Sky.cpp \
SkyAtlas/Model/Star.cpp \
SkyAtlas/View/Projection.cpp \
SkyAtlas/View/StereographicProjection.cpp

