#-------------------------------------------------
#
# Project created by QtCreator 2016-03-20T23:46:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MedAnalyser
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    dicomdirfile.cpp \
    imebradicomdirfile.cpp \
    dicompatient.cpp \
    imebradicompatient.cpp \
    imebraobject.cpp \
    dicomstudy.cpp \
    imebradicomstudy.cpp \
    dicomseries.cpp \
    imebradicomseries.cpp \
    dicomimage.cpp \
    imebradicomimage.cpp \
    cvimagewidge.cpp

HEADERS  += mainwindow.h \
    dicomdirfile.h \
    imebradicomdirfile.h \
    dicompatient.h \
    imebradicompatient.h \
    imebraobject.h \
    dicomstudy.h \
    imebradicomstudy.h \
    dicomseries.h \
    imebradicomseries.h \
    dicomimage.h \
    imebradicomimage.h \
    cvimagewidge.h

FORMS    += mainwindow.ui

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../imebra/build/ -limebra
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../imebra/build/ -limebrad
#else:unix: LIBS += -L$$PWD/../imebra/build/ -limebra

PRE_TARGETDEPS += $$PWD/../imebra/build/libimebra.a
PRE_TARGETDEPS += C:\Qt\Tools\mingw492_32\i686-w64-mingw32\lib\libiconv.a
INCLUDEPATH += $$PWD/../imebra/library
DEPENDPATH += $$PWD/../imebra/library
#win32:LIBS += -L$$PWD/../imebra/build/ -limebra
win32:LIBS += $$PWD/../imebra/build/libimebra.a
win32:LIBS += C:\Qt\Tools\mingw492_32\i686-w64-mingw32\lib\libiconv.a

INCLUDEPATH += $$PWD/../libmedimageanalyser
DEPENDPATH += $$PWD/../libmedimageanalyser
win32:LIBS += $$PWD/../libmedimageanalyser/build/libmedimageanalyser.a

#win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../imebra/build/libimebra.a
#else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../imebra/build/libimebrad.a
#else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../imebra/build/imebra.lib
#else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../imebra/build/imebrad.lib
#else:unix: PRE_TARGETDEPS += $$PWD/../imebra/build/libimebra.a

INCLUDEPATH += C:\\OpenCV-3.0.0\\mybuild_mingw\\install\\include

LIBS +=-LC:\\OpenCV-3.0.0\\mybuild_mingw\\install\\x86\\mingw\\bin \
    -llibopencv_calib3d300 \
    -llibopencv_core300 \
    -llibopencv_features2d300 \
    -llibopencv_flann300 \
    -llibopencv_highgui300 \
    -llibopencv_imgcodecs300 \
    -llibopencv_imgproc300 \
    -llibopencv_ml300 \
    -llibopencv_objdetect300 \
    -llibopencv_photo300 \
    -llibopencv_shape300 \
    -llibopencv_stitching300 \
    -llibopencv_superres300 \
    -llibopencv_video300 \
    -llibopencv_videoio300 \
    -llibopencv_videostab300 \
    -lopencv_ffmpeg300
