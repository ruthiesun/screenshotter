cmake_minimum_required(VERSION 3.5)

project(collectionmodel_test LANGUAGES CXX)

enable_testing()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Gui Test)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui Test)
find_package(Qt6 REQUIRED COMPONENTS Core)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(collectionmodel_test collectionmodel_test.cpp)
add_test(NAME collectionmodel_test COMMAND collectionmodel_test)

target_link_libraries(collectionmodel_test PRIVATE Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Test)

include_directories(../../src/app/)
