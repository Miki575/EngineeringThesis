QT += widgets
requires(qtConfig(combobox))

HEADERS     = dialog.h
SOURCES     = dialog.cpp \
              main.cpp

# install
target.path = /home/miki/repo/EngineeringThesis
INSTALLS += target
