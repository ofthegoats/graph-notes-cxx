TEMPLATE = app
TARGET = graph-notes-cxx
INCLUDEPATH += .

# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the documentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += database.hpp \
           graph.hpp \
           graph_notes.hpp \
           main_window.hpp \
           note_widget.hpp \
           draw_widget.hpp

SOURCES += database.cpp \
           graph.cpp \
           main_window.cpp \
           note_widget.cpp \
           draw_widget.cpp \
           main.cpp

QT += widgets
