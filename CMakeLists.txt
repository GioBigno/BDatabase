cmake_minimum_required(VERSION 3.16)

project(BDatabase VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(QT_QML_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR})

find_package(Qt6 6.2 COMPONENTS Quick Core Sql REQUIRED)

qt_add_library(BDatabase STATIC)
qt_add_qml_module(BDatabase
    URI BDatabase
    VERSION 1.0
    SOURCES bdatabase.cpp bdatabase.h
)

set_target_properties(BDatabase PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(BDatabase
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(BDatabase
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Core
    PRIVATE Qt6::Sql)

target_include_directories(BDatabase PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

qt6_generate_deploy_qml_app_script(
    TARGET BDatabase
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
    MACOS_BUNDLE_POST_BUILD
    DEPLOY_USER_QML_MODULES_ON_UNSUPPORTED_PLATFORM
)
install(SCRIPT ${deploy_script})
