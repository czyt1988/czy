DEFINES += GSL_DLL#此句不加将会遇到一些连接错误
INCLUDEPATH += $$PWD\include
DEPENDPATH += $$PWD
LIBS += -L$$PWD\lib -llibgsl
LIBS += -L$$PWD\lib -llibgslcblas
