TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

unix {
    LIBS += "../L_Renderer/libL_Renderer.a"
    LIBS += "../L_Physics/libL_Physics.a"
    LIBS += "../LEti_Engine/libLEti_Engine.a"
    LIBS += "../L_Gamedev_Lib/libL_Gamedev_Lib.a"
    LIBS += "../L_Variable/libL_Variable.a"
    LIBS += "../L_Utility/libL_Utility.a"

    LIBS += "../../LEti_Engine/OpenGL/Linux/lib/libglfw3.a"
    LIBS += "../../LEti_Engine/OpenGL/Linux/lib/libGLEW.a"

    LIBS += -lpthread -lGL -lX11 -ldl

    INCLUDEPATH += "../LEti_Engine/OpenGL/Linux/include/"
}


win32 {
    LIBS += "../L_Renderer/debug/libL_Renderer.a"
    LIBS += "../L_Physics/debug/libL_Physics.a"
    LIBS += "../LEti_Engine/debug/libLEti_Engine.a"
    LIBS += "../L_Gamedev_Lib/debug/libL_Gamedev_Lib.a"
    LIBS += "../L_Variable/debug/libL_Variable.a"
    LIBS += "../L_Utility/debug/libL_Utility.a"

    LIBS += "../../LEti_Engine/OpenGL/Windows_x64_mingw/lib/libglfw3.a"
    LIBS += "../../LEti_Engine/OpenGL/Windows_x64_mingw/lib/libglew32.a"

    LIBS += -lopengl32 \
	-luser32 \
	-lgdi32 \
	-lshell32

    LIBS += \
	-static-libstdc++ \
	-static-libgcc

    INCLUDEPATH += "../LEti_Engine/OpenGL/Windows_x64_mingw/include/"
}

INCLUDEPATH += "../LEti_Engine/OpenGL/GLM"
INCLUDEPATH += "../LEti_Engine/OpenGL/"

INCLUDEPATH += "include/"
INCLUDEPATH += "../L_Utility/include/"
INCLUDEPATH += "../L_Variable/include/"
INCLUDEPATH += "../L_Gamedev_Lib/include/"
INCLUDEPATH += "../LEti_Engine/include/"
INCLUDEPATH += "../L_Renderer/include/"
INCLUDEPATH += "../L_Physics/include/"


SOURCES += \
	Main.cpp \
	source/Screen.cpp \
	source/UI_Object_Stub.cpp



#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../LEti_Engine/OpenGL/GLFW/lib/ -lglfw3
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../LEti_Engine/OpenGL/GLFW/lib/ -lglfw3

HEADERS += \
	include/Screen.h \
	include/UI_Object_Stub.h

DISTFILES += \
    Resources/Font/font_yellow.mdl \
    Resources/Font/small_font.mdl \
    Resources/Models/old/colliding_object.mdl \
    Resources/Models/old/debug_frame.mdl \
    Resources/Models/old/debug_frame_red.mdl \
    Resources/Models/old/flat_co.mdl \
    Resources/Models/old/flat_co_2.mdl \
    Resources/Models/old/flat_colliding_object.mdl \
    Resources/Models/old/flat_cos/flat_co_1.mdl \
    Resources/Models/old/flat_cos/flat_co_2.mdl \
    Resources/Models/old/flat_cos/flat_co_3.mdl \
    Resources/Models/old/flat_indicator_red.mdl \
    Resources/Models/old/intersection_indicator_3d.mdl \
    Resources/Models/old/intersection_point_indicator.mdl \
    Resources/Models/old/pyramid.mdl \
    Resources/Models/old/quad.mdl \
    Resources/Models/old/red_cube.mdl \
    Resources/Models/old/text_field.mdl \
    Resources/Models/old/triangle.mdl \
    Resources/Models/quad_new.mdl \
    Resources/Models/screen_test.mdl \
    Resources/Models/text_field_new.mdl \
    Resources/Models/triangle.mdl \
    Resources/Models/ui_object_stub_test.mdl \
    Resources/Textures/textures.mdl
