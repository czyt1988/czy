INCLUDEPATH += $$PWD\include
INCLUDEPATH += $$PWD\fftw
DEPENDPATH += $$PWD\include

HEADERS += \
        $$PWD/czyMath.h \

LIBS += -L$$PWD\fftw -llibfftw3-3
