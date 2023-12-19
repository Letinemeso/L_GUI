cmake_minimum_required(VERSION 3.5)

project(L_GUI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

FILE(GLOB_RECURSE LibFiles "include/*.h")
add_custom_target(_L_GUI_include SOURCES ${LibFiles})
FILE(GLOB_RECURSE Models "Resources/*")
add_custom_target(L_GUI_models SOURCES ${Models})


file(GLOB_RECURSE Sources "source/*.cpp")
add_executable(L_GUI ${Sources} Main.cpp)

add_subdirectory("${PROJECT_SOURCE_DIR}/../L_Utility"
                 "${PROJECT_BINARY_DIR}/../L_Utility"
)
add_subdirectory("${PROJECT_SOURCE_DIR}/../L_Variable"
                 "${PROJECT_BINARY_DIR}/../L_Variable"
)
add_subdirectory("${PROJECT_SOURCE_DIR}/../LEti_Engine"
                 "${PROJECT_BINARY_DIR}/../LEti_Engine"
)
add_subdirectory("${PROJECT_SOURCE_DIR}/../L_Renderer"
                 "${PROJECT_BINARY_DIR}/../L_Renderer"
)
add_subdirectory("${PROJECT_SOURCE_DIR}/../L_Physics"
                 "${PROJECT_BINARY_DIR}/../L_Physics"
)
add_subdirectory("${PROJECT_SOURCE_DIR}/../L_Gamedev_Lib"
                 "${PROJECT_BINARY_DIR}/../L_Gamedev_Lib"
)

target_include_directories(L_GUI PUBLIC
                            "${PROJECT_SOURCE_DIR}"
                            "${PROJECT_SOURCE_DIR}/include"
                            "${PROJECT_SOURCE_DIR}/../L_Utility/include"
                            "${PROJECT_SOURCE_DIR}/../L_Variable/include"
                            "${PROJECT_SOURCE_DIR}/../LEti_Engine/include"
                            "${PROJECT_SOURCE_DIR}/../LEti_Engine/OpenGL/GLM"
                            "${PROJECT_SOURCE_DIR}/../L_Renderer/include"
                            "${PROJECT_SOURCE_DIR}/../L_Physics/include"
                            "${PROJECT_SOURCE_DIR}/../L_Gamedev_Lib/include"
)


target_include_directories(L_GUI PUBLIC "${PROJECT_SOURCE_DIR}/../L_Renderer/OpenGL/include" )


target_link_libraries(L_GUI PUBLIC
    L_Gamedev_Lib
    L_Physics
    L_Renderer
    LEti_Engine
    L_Variable
    L_Utility
)

add_library(glfw STATIC IMPORTED)
add_library(glew STATIC IMPORTED)

if(MSVC)
    set_target_properties(glfw PROPERTIES IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/../Third_Party/libglfw3.lib")
    set_target_properties(glew PROPERTIES IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/../Third_Party/libglew32.lib")
else()
    set_target_properties(glfw PROPERTIES IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/../Third_Party/libglfw3.a")
    set_target_properties(glew PROPERTIES IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/../Third_Party/libglew32.a")
endif(MSVC)

target_link_libraries(L_GUI PUBLIC
    glfw
    glew
)

if (WIN32)
    target_link_libraries(L_GUI PUBLIC
        opengl32
        user32
        gdi32
        shell32
    )
endif (WIN32)

if (UNIX)
    target_link_libraries(L_GUI PUBLIC
        pthread
        GL
        X11
        dl
    )
endif (UNIX)
