cmake_minimum_required(VERSION 2.8.12)

project(Demo_PureMvc)

# CMake会自动查找和处理所有包含了Q_OBJECT宏的类，并通过moc（元对象编译器）生成对应的.moc文件。
# 在Qt中使用信号和槽、以及某些其他特性时就需要这些.moc文件。因此开启此选项可以简化编译过程。
set(CMAKE_AUTOMOC ON)
# 当开启此选项时，CMake会自动查找并处理UI文件（.ui），并生成相应的头文件（ui_*.h）供项目中使用。
set(CMAKE_AUTOUIC ON)
# CMake会自动查找并处理资源文件（如.qrc文件），并将其转换为对应的资源描述头文件供项目使用。
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

aux_source_directory(Core SRC)
aux_source_directory(Patterns SRC)
aux_source_directory(MySqlDBManager SRC)
aux_source_directory(Util SRC)
aux_source_directory(. SRC)
file(GLOB INC "Core/*.h" "Interface/*.h" "Patterns/*.h" "MySqlDBManager/*.h" "./*.h "Util/*.h"")
file(GLOB UI "./*.ui")

message(STATUS "SRC: ${SRC}")
message(STATUS "INC: ${INC}")
message(STATUS "UI: ${UI}")

# 01 Login
aux_source_directory(01_Login 01_SRC)
file(GLOB 01_INC "01_Login/*.h")
file(GLOB 01_UI "01_Login/*.ui")

message(STATUS "01_SRC: ${01_SRC}")
message(STATUS "01_INC: ${01_INC}")
message(STATUS "01_UI: ${01_UI}")

# 02 PrimaryService
aux_source_directory(02_PrimaryService 02_SRC)
file(GLOB 02_INC "02_PrimaryService/*.h")
file(GLOB 02_UI "02_PrimaryService/*.ui")

message(STATUS "02_SRC: ${02_SRC}")
message(STATUS "02_INC: ${02_INC}")
message(STATUS "02_UI: ${02_UI}")


list(APPEND CMAKE_AUTOUIC_SEARCH_PATHS "02_PrimaryService")

# 获取查找结果，存储到变量中 Widgets Network Multimedia
find_package(QT NAMES Qt5 Qt6 COMPONENTS Widgets Network Multimedia Charts Sql REQUIRED)
# 根据上面的结果去获取package Widgets Network Multimedia
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Network Multimedia Charts Sql REQUIRED)
# 最后查看获取的情况
if(Qt${QT_VERSION_MAJOR}_FOUND)
    message(STATUS "Found Qt version: ${Qt${QT_VERSION_MAJOR}_VERSION}")
    # Additional configuration or settings if Qt is found
else()
    message(FATAL_ERROR "Qt not found. Please check your Qt installation.")
endif()

# 添加该行用于将include目录添加到头文件搜索路径中
include_directories("Util" "Core" "Interface" "Patterns" "MySqlDBManager" "." "01_Login" "02_PrimaryService")

# 使用自动查找的存储的变量
add_executable(${PROJECT_NAME}
    "main.cpp"
    ${INC}
    ${SRC}
    ${UI}
    ${01_INC}
    ${01_SRC}
    ${01_UI}
    ${02_INC}
    ${02_SRC}
    ${02_UI}
    )

target_include_directories(${PROJECT_NAME} PUBLIC $<TARGET_FILE_DIR:${PROJECT_NAME}>)

# 指定Qt依赖库和头文件
target_link_libraries(${PROJECT_NAME} Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
    Qt${QT_VERSION_MAJOR}::Multimedia
    Qt${QT_VERSION_MAJOR}::Charts
    Qt${QT_VERSION_MAJOR}::Sql
    )
