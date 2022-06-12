cmake_minimum_required(VERSION 3.5)

project(all_tests LANGUAGES CXX)

enable_testing()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Gui Test)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui Test)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(all_tests
    collectionmodel_test/collectionmodel_test.cpp
)

add_test(NAME all_tests COMMAND all_tests)

target_link_libraries(all_tests PRIVATE Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Test)

add_subdirectory(collectionmodel_test/)

include_directories(../src/app/)
