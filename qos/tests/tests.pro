QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

include(../qosbrowser/qosbrowser.pri)

# 不再需要了
# win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../qosbrowser/third/cos/libs/x64/ -lcossdk
# else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../qosbrowser/third/cos/libs/x64/ -lcossdk
# else:unix: LIBS += -L$$PWD/../qosbrowser/third/cos/libs/x64/ -lcossdk

# win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../qosbrowser/third/cos/third_party/lib/x64/poco -lPocoFoundation
# else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../qosbrowser/third/cos/third_party/lib/x64/poco -lPocoFoundation
# else:unix: LIBS += -L$$PWD/../qosbrowser/third/cos/third_party/lib/x64/poco -lPocoFoundation

# INCLUDEPATH += $$PWD/../qosbrowser/third/cos/include \
#     $$PWD/../qosbrowser/third/cos/third_party/include
# DEPENDPATH += $$PWD/../qosbrowser/third/cos/include \
#     $$PWD/../qosbrowser/third/cos/third_party/include


SOURCES += \
    # ../qosbrowser/src/bend/dao/clouds/daocloudscos.cpp \
    # ../qosbrowser/src/config/exceptions.cpp \
    # ../qosbrowser/src/helper/filehelper.cpp \
    # ../qosbrowser/src/middle/models/cloudmodels.cpp \
    main.cpp \
    testcos/tst_testcos.cpp \
    testexceptions/tst_testexceptions.cpp \
    testfilehelper/tst_testfilehelper.cpp

INCLUDEPATH += \
 ../qosbrowser

HEADERS += \
    # ../qosbrowser/src/bend/dao/clouds/daoclouds.h \
    # ../qosbrowser/src/bend/dao/clouds/daocloudscos.h \
    # ../qosbrowser/src/config/errorcode.h \
    # ../qosbrowser/src/config/exceptions.h \
    # ../qosbrowser/src/helper/filehelper.h \
    # ../qosbrowser/src/middle/models/cloudmodels.h \
    testcos/tst_testcos.h \
    testexceptions/tst_testexceptions.h \
    testfilehelper/tst_testfilehelper.h

RESOURCES += \
    resource.qrc
