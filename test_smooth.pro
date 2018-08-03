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
    #run_bacf.cpp \
    #bacf_optimized.cpp \
    get_pixels.cpp \
    mexresize.cpp \
    get_features.cpp \
    get_fhog.cpp \
    get_subwindow_no_window.cpp \
    resizedft2.cpp \
    resp_newton.cpp \
    test.cpp \
    piotr_fhog/gradientMex.cpp \
    thread_bacf_tracking.cpp \
    widget.cpp \
    func.cpp

HEADERS += \
        mainwindow.h \
    load_video_info.h \
    #run_bacf.h \
    #bacf_optimized.h \
    get_pixels.h \
    mexresize.h \
    get_features.h \
    get_fhog.h \
    fhog.hpp \
    get_subwindow_no_window.h \
    resizedft2.h \
    resp_newton.h \
    test.h \
    piotr_fhog/fhog.hpp \
    piotr_fhog/gradientMex.h \
    piotr_fhog/sse.hpp \
    piotr_fhog/wrappers.hpp \
    thread_bacf_tracking.h \
    widget.h \
    func.h

FORMS += \
        mainwindow.ui

INCLUDEPATH += C:/Users/Eilin/Downloads/opencv/build/include/opencv
INCLUDEPATH += C:/Users/Eilin/Downloads/opencv/build/include/opencv2
INCLUDEPATH += C:/Users/Eilin/Downloads/opencv/build/include
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

LIBS+=-LC:/Users/Eilin/Downloads/opencv/build/x64/vc12/lib -lopencv_calib3d2410
LIBS+=-LC:/Users/Eilin/Downloads/opencv/build/x64/vc12/lib -lopencv_core2410
#LIBS+=-LC:/Users/Eilin/Downloads/opencv/build/x64/vc12/lib -lopencv_dnn2410
LIBS+=-LC:/Users/Eilin/Downloads/opencv/build/x64/vc12/lib -lopencv_features2d2410
LIBS+=-LC:/Users/Eilin/Downloads/opencv/build/x64/vc12/lib -lopencv_flann2410
LIBS+=-LC:/Users/Eilin/Downloads/opencv/build/x64/vc12/lib -lopencv_highgui2410
#LIBS+=-LC:/Users/Eilin/Downloads/opencv/build/x64/vc12/lib -lopencv_imgcodecs2410
LIBS+=-LC:/Users/Eilin/Downloads/opencv/build/x64/vc12/lib -lopencv_imgproc2410
LIBS+=-LC:/Users/Eilin/Downloads/opencv/build/x64/vc12/lib -lopencv_ml2410
LIBS+=-LC:/Users/Eilin/Downloads/opencv/build/x64/vc12/lib -lopencv_objdetect2410
LIBS+=-LC:/Users/Eilin/Downloads/opencv/build/x64/vc12/lib -lopencv_photo2410
#LIBS+=-LC:/Users/Eilin/Downloads/opencv/build/x64/vc12/lib -lopencv_shape2410
LIBS+=-LC:/Users/Eilin/Downloads/opencv/build/x64/vc12/lib -lopencv_stitching2410
LIBS+=-LC:/Users/Eilin/Downloads/opencv/build/x64/vc12/lib -lopencv_superres2410
LIBS+=-LC:/Users/Eilin/Downloads/opencv/build/x64/vc12/lib -lopencv_video2410
#LIBS+=-LC:/Users/Eilin/Downloads/opencv/build/x64/vc12/lib -lopencv_videoio2410
LIBS+=-LC:/Users/Eilin/Downloads/opencv/build/x64/vc12/lib -lopencv_videostab2410
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

