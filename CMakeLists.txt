cmake_minimum_required(VERSION 3.21)

project(RayTracer)
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE
    SOURCE_FILES
    Source/*.cpp
    Source/*.hpp
)
set(INCLUDE_DIRS
    Source
    Source/Vendor
    Source/Vendor/GLFW/include
    Source/Vendor/glm
)
set(LIB_LINKS
    ${CMAKE_SOURCE_DIR}/Source/Vendor/GLFW/lib/glfw3.lib
)

add_executable(RayTracer ${SOURCE_FILES})
target_include_directories(RayTracer PRIVATE ${INCLUDE_DIRS})
target_link_libraries(RayTracer PRIVATE ${LIB_LINKS} ${DX11_LIBS})
set_property(TARGET RayTracer PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
