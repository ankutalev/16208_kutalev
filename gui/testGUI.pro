#-------------------------------------------------
#
# Project created by QtCreator 2017-12-21T23:56:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testGUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ../core_war/renderarea.cpp \
    controller.cpp \
    ../../CLionProjects/obertka_repo/16208_kutalev/core_war/mars.cpp \
    ../../CLionProjects/obertka_repo/16208_kutalev/core_war/warrior.cpp \
    ../../CLionProjects/obertka_repo/16208_kutalev/core_war/add_command.cpp \
    ../../CLionProjects/obertka_repo/16208_kutalev/core_war/CircularBuffer.cpp \
    ../../CLionProjects/obertka_repo/16208_kutalev/core_war/dat_command.cpp \
    ../../CLionProjects/obertka_repo/16208_kutalev/core_war/div_command.cpp \
    ../../CLionProjects/obertka_repo/16208_kutalev/core_war/djn_command.cpp \
    ../../CLionProjects/obertka_repo/16208_kutalev/core_war/factory.cpp \
    ../../CLionProjects/obertka_repo/16208_kutalev/core_war/instructions.cpp \
    ../../CLionProjects/obertka_repo/16208_kutalev/core_war/jmn_command.cpp \
    ../../CLionProjects/obertka_repo/16208_kutalev/core_war/jmp_command.cpp \
    ../../CLionProjects/obertka_repo/16208_kutalev/core_war/jmz_command.cpp \
    ../../CLionProjects/obertka_repo/16208_kutalev/core_war/mov_command.cpp \
    ../../CLionProjects/obertka_repo/16208_kutalev/core_war/mul_command.cpp \
    ../../CLionProjects/obertka_repo/16208_kutalev/core_war/nop_command.cpp \
    ../../CLionProjects/obertka_repo/16208_kutalev/core_war/seq_command.cpp \
    ../../CLionProjects/obertka_repo/16208_kutalev/core_war/slt_command.cpp \
    ../../CLionProjects/obertka_repo/16208_kutalev/core_war/sne_command.cpp \
    ../../CLionProjects/obertka_repo/16208_kutalev/core_war/spl_command.cpp \
    ../../CLionProjects/obertka_repo/16208_kutalev/core_war/sub_command.cpp \
    ../../CLionProjects/obertka_repo/16208_kutalev/core_war/DefaultContext.cpp \
    ../../CLionProjects/obertka_repo/16208_kutalev/core_war/loader.cpp \
    info.cpp \
    winners.cpp \
    model.cpp

HEADERS  += mainwindow.h \
    ../core_war/renderarea.h \
    controller.h \
    ../../CLionProjects/obertka_repo/16208_kutalev/core_war/mars.h \
    ../../CLionProjects/obertka_repo/16208_kutalev/core_war/warrior.hpp \
    ../../CLionProjects/obertka_repo/16208_kutalev/core_war/CircularBuffer.hpp \
    ../../CLionProjects/obertka_repo/16208_kutalev/core_war/DefaultContext.hpp \
    ../../CLionProjects/obertka_repo/16208_kutalev/core_war/ExecutionContext.h \
    ../../CLionProjects/obertka_repo/16208_kutalev/core_war/factory.hpp \
    ../../CLionProjects/obertka_repo/16208_kutalev/core_war/instructions.hpp \
    ../../CLionProjects/obertka_repo/16208_kutalev/core_war/loader.hpp \
    ../../CLionProjects/obertka_repo/16208_kutalev/core_war/template_hash_table.hpp \
    info.h \
    winners.h \
    model.h

FORMS    += mainwindow.ui

RESOURCES += \
    guirsc.qrc
