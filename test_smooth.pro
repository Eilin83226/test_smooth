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
    #run_bacf.cpp \
    #bacf_optimized.cpp \
    get_pixels.cpp \
    mexresize.cpp \
    get_features.cpp \
    get_fhog.cpp \
    get_subwindow_no_window.cpp \
    resizedft2.cpp \
    resp_newton.cpp \
    piotr_fhog/gradientMex.cpp \
    thread_bacf_tracking.cpp \
    func.cpp

HEADERS += \
        mainwindow.h \
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
    piotr_fhog/fhog.hpp \
    piotr_fhog/gradientMex.h \
    piotr_fhog/sse.hpp \
    piotr_fhog/wrappers.hpp \
    thread_bacf_tracking.h \
    func.h \
    piotr_fhog/fhog.hpp \
    piotr_fhog/gradientMex.h \
    piotr_fhog/sse.hpp \
    piotr_fhog/wrappers.hpp

FORMS += \
        mainwindow.ui

INCLUDEPATH += E:/opencv_build_vs2013/install/include/opencv
INCLUDEPATH += E:/opencv_build_vs2013/install/include/opencv2
INCLUDEPATH += E:/opencv_build_vs2013/install/include
INCLUDEPATH += C:/Qt/5.5/msvc2013_64/include
INCLUDEPATH += E:/mexopencv-master/include
#INCLUDEPATH += E:/Robust-View-Graph-SLAM-master/matlab/include
#INCLUDEPATH += $$quote(C:\Program Files\MATLAB\R2015b\extern\include)
#INCLUDEPATH += $$quote(C:\Program Files\MATLAB\R2015b\extern\include\win64)
#INCLUDEPATH += $$quote(C:\Program Files\MATLAB\R2015b\extern\lib\win64\mingw64)

# .h文件搜索路径
#INCLUDEPATH += C:/Matlab2015b/extern/include
#INCLUDEPATH += C:/Matlab2015b/extern/include/win64

# 用到的MATLAB 的.lib库文件 及其搜索路径
#INCLUDEPATH += C:/Matlab2015b/extern/lib/win64/microsoft
#DEPENDPATH += C:/Matlab2015b/extern/lib/win64/microsoft

#win32: LIBS+=-LC:/Matlab2015b/extern/lib/win64/microsoft -llibmex
#win32: LIBS+=-LC:/Matlab2015b/extern/lib/win64/microsoft -llibmx
#win32: LIBS+=-LC:/Matlab2015b/extern/lib/win64/microsoft -llibmat
#win32: LIBS+=-LC:/Matlab2015b/extern/lib/win64/microsoft -llibeng
#win32: LIBS+=-LC:/Matlab2015b/extern/lib/win64/microsoft -lmclmcr
#win32: LIBS+=-LC:/Matlab2015b/extern/lib/win64/microsoft -lmclmcrrt
#win32: LIBS+=-LC:/Matlab2015b/extern/lib/win64/microsoft -llibmwblas


#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/mtimesx/for_redistribution_files_only/ -lmtimesx
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/mtimesx/for_redistribution_files_only/ -lmtimesxd

#INCLUDEPATH += $$PWD/mtimesx/for_redistribution_files_only
#DEPENDPATH += $$PWD/mtimesx/for_redistribution_files_only

LIBS+=-LE:/opencv_build_vs2013/install/x64/vc12/lib -lopencv_calib3d341
LIBS+=-LE:/opencv_build_vs2013/install/x64/vc12/lib -lopencv_core341
#LIBS+=-LE:/opencv_build_vs2013/install/x64/vc12/lib -lopencv_contrib341
LIBS+=-LE:/opencv_build_vs2013/install/x64/vc12/lib -lopencv_dnn341
LIBS+=-LE:/opencv_build_vs2013/install/x64/vc12/lib -lopencv_features2d341
LIBS+=-LE:/opencv_build_vs2013/install/x64/vc12/lib -lopencv_flann341
#LIBS+=-LE:/opencv_build_vs2013/install/x64/vc12/lib -lopencv_gpu341
LIBS+=-LE:/opencv_build_vs2013/install/x64/vc12/lib -lopencv_highgui341
LIBS+=-LE:/opencv_build_vs2013/install/x64/vc12/lib -lopencv_imgcodecs341
LIBS+=-LE:/opencv_build_vs2013/install/x64/vc12/lib -lopencv_imgproc341
#LIBS+=-LE:/opencv_build_vs2013/install/x64/vc12/lib -lopencv_legacy341
LIBS+=-LE:/opencv_build_vs2013/install/x64/vc12/lib -lopencv_ml341
#LIBS+=-LE:/opencv_build_vs2013/install/x64/vc12/lib -lopencv_nonfree341
LIBS+=-LE:/opencv_build_vs2013/install/x64/vc12/lib -lopencv_objdetect341
#LIBS+=-LE:/opencv_build_vs2013/install/x64/vc12/lib -lopencv_ocl341
LIBS+=-LE:/opencv_build_vs2013/install/x64/vc12/lib -lopencv_photo341
LIBS+=-LE:/opencv_build_vs2013/install/x64/vc12/lib -lopencv_shape341
LIBS+=-LE:/opencv_build_vs2013/install/x64/vc12/lib -lopencv_stitching341
LIBS+=-LE:/opencv_build_vs2013/install/x64/vc12/lib -lopencv_superres341
LIBS+=-LE:/opencv_build_vs2013/install/x64/vc12/lib -lopencv_video341
LIBS+=-LE:/opencv_build_vs2013/install/x64/vc12/lib -lopencv_videoio341
LIBS+=-LE:/opencv_build_vs2013/install/x64/vc12/lib -lopencv_videostab341
#LIBS+=-L$$quote(C:/Program Files (x86)/Microsoft SDKs/Windows/v7.1A/Lib/x64) -lGdi32
#LIBS+=-L$$quote(C:/Program Files (x86)/Microsoft SDKs/Windows/v7.1A/Lib/x64) -lUser32
          -lGdi32




