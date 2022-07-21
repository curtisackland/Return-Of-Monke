QT       += core widgets
TARGET = TestSuite
TEMPLATE = app 
SOURCES += testSuite.cpp bullet.cpp inventory.cpp gun.cpp player.cpp enemy.cpp HUDbar.cpp menuButton.cpp
HEADERS += testSuite.h bullet.h inventory.h gun.h player.h enemy.h HUDbar.h menuButton.h
LIBS += -lboost_unit_test_framework
QMAKE_CXXFLAGS += -g -O0