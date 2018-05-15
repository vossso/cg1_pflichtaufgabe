QT       += core gui opengl widgets

TEMPLATE = app

TARGET = CgQtViewer

SOURCES += main.cpp \
    CgQtViewer/CGQtGLRenderWidget.cpp \
    CgQtViewer/CgQtGui.cpp \
    CgBase/CgObservable.cpp \
    CgEvents/CgMouseEvent.cpp \
    CgQtViewer/CgQtMainApplication.cpp \
    CgSceneGraph/CgSceneControl.cpp \
    CgEvents/CgKeyEvent.cpp \
    CgSceneGraph/CgExampleTriangle.cpp \
    CgQtViewer/CgQtGlBufferObject.cpp \
    CgQtViewer/CgTrackball.cpp \
    CgEvents/CgWindowResizeEvent.cpp \
    CgSceneGraph/CgCube.cpp \
    CgSceneGraph/CgMyPolyline.cpp \
    CgSceneGraph/CgZylinder.cpp \
    CgEvents/ChSliderChangeEvent.cpp \
    CgSceneGraph/CgCone.cpp \
    CgEvents/CgSpinboxEvent.cpp \
    CgEvents/CgCheckBoxEvent.cpp \
    CgSceneGraph/CgIdCounter.cpp

HEADERS += \
    CgBase/CgBaseRenderWindow.h \
    CgQtViewer/CgQtGLRenderWidget.h \
    CgQtViewer/CgQtGui.h \
    CgBase/CgObserver.h \
    CgBase/CgObservable.h \
    CgBase/CgBaseEvent.h \
    CgBase/CgEnums.h \
    CgEvents/CgMouseEvent.h \
    CgQtViewer/CgQtMainApplication.h \
    CgSceneGraph/CgSceneControl.h \
    CgEvents/CgKeyEvent.h \
    CgBase/CgBaseRenderer.h \
    CgBase/CgBaseRenderableObject.h \
    CgSceneGraph/CgExampleTriangle.h \
    CgBase/CgBasePointCloud.h \
    CgBase/CgBaseTriangleMesh.h \
    CgBase/CgBasePolygonMesh.h \
    CgBase/CgBasePolyline.h \
    CgBase/CgBaseSceneControl.h \
    CgQtViewer/CgQtGlBufferObject.h \
    CgQtViewer/CgTrackball.h \
    CgEvents/CgWindowResizeEvent.h \
    CgSceneGraph/CgCube.h \
    CgSceneGraph/CgMyPolyline.h \
    CgSceneGraph/CgZylinder.h \
    CgEvents/CgSliderChangeEvent.h \
    CgSceneGraph/CgCone.h \
    CgEvents/CgSpinboxEvent.h \
    CgEvents/CgCheckBoxEvent.h \
    CgSceneGraph/CgIdCounter.h

DISTFILES +=

