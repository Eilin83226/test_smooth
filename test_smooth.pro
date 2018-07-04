#-------------------------------------------------
#
# Project created by QtCreator 2018-03-01T14:52:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test_smooth
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    load_video_info.cpp \
    run_bacf.cpp \
    bacf_optimized.cpp \
    get_pixels.cpp \
    mexresize.cpp \
    get_features.cpp \
    get_fhog.cpp \
    piotr_fhog/gradientMex.cpp \
    get_subwindow_no_window.cpp \
    resizedft2.cpp \
    resp_newton.cpp \
    test.cpp

HEADERS += \
        mainwindow.h \
    load_video_info.h \
    run_bacf.h \
    bacf_optimized.h \
    get_pixels.h \
    mexresize.h \
    get_features.h \
    get_fhog.h \
    fhog.hpp \
    piotr_fhog/fhog.hpp \
    piotr_fhog/gradientMex.h \
    piotr_fhog/sse.hpp \
    piotr_fhog/wrappers.hpp \
    FHOG-master/pdollar/fhog.h \
    FHOG-master/pdollar/sse.hpp \
    FHOG-master/pdollar/SSE2NEON.h \
    get_subwindow_no_window.h \
    resizedft2.h \
    resp_newton.h \
    test.h

FORMS += \
        mainwindow.ui

INCLUDEPATH += E:/opencv_build_vs2013/install/include/opencv
INCLUDEPATH += E:/opencv_build_vs2013/install/include/opencv2
INCLUDEPATH += E:/opencv_build_vs2013/install/include
INCLUDEPATH += C:/Qt/5.5/msvc2013_64/include
INCLUDEPATH += E:/mexopencv-master/include
INCLUDEPATH += E:/Robust-View-Graph-SLAM-master/matlab/include
#INCLUDEPATH += $$quote(C:\Program Files\MATLAB\R2015b\extern\include)
#INCLUDEPATH += $$quote(C:\Program Files\MATLAB\R2015b\extern\include\win64)
#INCLUDEPATH += $$quote(C:\Program Files\MATLAB\R2015b\extern\lib\win64\mingw64)

# .h文件搜索路径
INCLUDEPATH += C:/Matlab2015b/extern/include
INCLUDEPATH += C:/Matlab2015b/extern/include/win64

# 用到的MATLAB 的.lib库文件 及其搜索路径
INCLUDEPATH += C:/Matlab2015b/extern/lib/win64/microsoft
DEPENDPATH += C:/Matlab2015b/extern/lib/win64/microsoft

win32: LIBS+=-LC:/Matlab2015b/extern/lib/win64/microsoft -llibmex
win32: LIBS+=-LC:/Matlab2015b/extern/lib/win64/microsoft -llibmx
win32: LIBS+=-LC:/Matlab2015b/extern/lib/win64/microsoft -llibmat
win32: LIBS+=-LC:/Matlab2015b/extern/lib/win64/microsoft -llibeng
win32: LIBS+=-LC:/Matlab2015b/extern/lib/win64/microsoft -lmclmcr
win32: LIBS+=-LC:/Matlab2015b/extern/lib/win64/microsoft -lmclmcrrt
win32: LIBS+=-LC:/Matlab2015b/extern/lib/win64/microsoft -llibmwblas


#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/mtimesx/for_redistribution_files_only/ -lmtimesx
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/mtimesx/for_redistribution_files_only/ -lmtimesxd

#INCLUDEPATH += $$PWD/mtimesx/for_redistribution_files_only
#DEPENDPATH += $$PWD/mtimesx/for_redistribution_files_only

LIBS+=-LE:/opencv_build_vs2013/install/x64/vc12/lib -lopencv_calib3d341
LIBS+=-LE:/opencv_build_vs2013/install/x64/vc12/lib -lopencv_core341
LIBS+=-LE:/opencv_build_vs2013/install/x64/vc12/lib -lopencv_dnn341
LIBS+=-LE:/opencv_build_vs2013/install/x64/vc12/lib -lopencv_features2d341
LIBS+=-LE:/opencv_build_vs2013/install/x64/vc12/lib -lopencv_flann341
LIBS+=-LE:/opencv_build_vs2013/install/x64/vc12/lib -lopencv_highgui341
LIBS+=-LE:/opencv_build_vs2013/install/x64/vc12/lib -lopencv_imgcodecs341
LIBS+=-LE:/opencv_build_vs2013/install/x64/vc12/lib -lopencv_imgproc341
LIBS+=-LE:/opencv_build_vs2013/install/x64/vc12/lib -lopencv_ml341
LIBS+=-LE:/opencv_build_vs2013/install/x64/vc12/lib -lopencv_objdetect341
LIBS+=-LE:/opencv_build_vs2013/install/x64/vc12/lib -lopencv_photo341
LIBS+=-LE:/opencv_build_vs2013/install/x64/vc12/lib -lopencv_shape341
LIBS+=-LE:/opencv_build_vs2013/install/x64/vc12/lib -lopencv_stitching341
LIBS+=-LE:/opencv_build_vs2013/install/x64/vc12/lib -lopencv_superres341
LIBS+=-LE:/opencv_build_vs2013/install/x64/vc12/lib -lopencv_video341
LIBS+=-LE:/opencv_build_vs2013/install/x64/vc12/lib -lopencv_videoio341
LIBS+=-LE:/opencv_build_vs2013/install/x64/vc12/lib -lopencv_videostab341
          -lGdi32


#          E:\opencvResult\openCV\bin\libopencv_calib3d249.dll \
#          E:\opencvResult\openCV\bin\libopencv_contrib249.dll \
#          E:\opencvResult\openCV\bin\libopencv_core249.dll \
#          E:\opencvResult\openCV\bin\libopencv_features2d249.dll \
#          E:\opencvResult\openCV\bin\libopencv_flann249.dll \
#          E:\opencvResult\openCV\bin\libopencv_gpu249.dll \
#          E:\opencvResult\openCV\bin\libopencv_highgui249.dll \
#          E:\opencvResult\openCV\bin\libopencv_imgproc249.dll \
#          E:\opencvResult\openCV\bin\libopencv_legacy249.dll \
#          E:\opencvResult\openCV\bin\libopencv_ml249.dll \
#          E:\opencvResult\openCV\bin\libopencv_nonfree249.dll \
#          E:\opencvResult\openCV\bin\libopencv_objdetect249.dll \
#          E:\opencvResult\openCV\bin\libopencv_ocl249.dll \
#          E:\opencvResult\openCV\bin\libopencv_photo249.dll \
#          E:\opencvResult\openCV\bin\libopencv_stitching249.dll \
#          E:\opencvResult\openCV\bin\libopencv_superres249.dll \
#          E:\opencvResult\openCV\bin\libopencv_video249.dll \
#          E:\opencvResult\openCV\bin\libopencv_videostab249.dll\
#          -lGdi32

QMAKE_CXXFLAGS += -msse3

QMAKE_CXXFLAGS += -std=c++0x
CONFIG += c++11


win32: LIBS += -L$$PWD/./ -lmyFunc

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

win32: LIBS += -L$$PWD/./ -lQTmtimesx

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

win32: LIBS += -L$$PWD/./ -lQTbsxfun

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

win32: LIBS += -L$$PWD/./ -lQTexp

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

