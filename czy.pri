INCLUDEPATH += $$PWD\include
INCLUDEPATH += $$PWD\3rdParty\fftw
DEPENDPATH += $$PWD\include

HEADERS += \
        $$PWD/czyMath.h \

LIBS += -L$$PWD\3rdParty\fftw -llibfftw3-3
