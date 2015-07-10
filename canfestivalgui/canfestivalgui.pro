TEMPLATE = app
TARGET =
DEPENDPATH += . include
INCLUDEPATH += . include

QT += qt3support

# Input
HEADERS += canfestivalgui.h \
           logthread.h \
           maingui.h \
           processvargui.h \
           pvargui.h \
           include/ArbraCan.h \
           include/Can.h \
           include/CanOpenMatic.h \
           maingui.moc \
           processvargui.moc
FORMS += maingui.ui processvargui.ui
SOURCES += canfestivalgui.cpp \
           CanOpenMatic.c \
           logthread.cpp \
           main.cpp \
           maingui.cpp \
           processvargui.cpp \
           pvargui.cpp
