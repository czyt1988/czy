INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD\fftw
DEPENDPATH += $$PWD

include($$PWD/gsl/gsl.pri)#the gsl lib support

HEADERS += $$PWD/czyQtApp.h\
        $$PWD/czyQArrayEx.h \
        $$PWD/czyQtUI.h \
        $$PWD/czyMath_DSP.h \
        $$PWD/czyMath.h \
        $$PWD/fftw/fftw3.h \
    $$PWD/czyMath_Interpolation.h \
    $$PWD/czyMath_Fit.h

SOURCES +=  $$PWD/czyMath_DSP.cpp\
		$$PWD/czyQtUI.cpp


LIBS += -L$$PWD\fftw -llibfftw3-3
