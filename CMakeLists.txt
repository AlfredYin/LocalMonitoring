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
aux_source_directory(Model SRC)
aux_source_directory(Controller SRC)
aux_source_directory(. SRC)
file(GLOB INC "Core/*.h" "Interface/*.h" "Patterns/*.h" "Model/*.h")

message(STATUS "SRC: ${SRC}")
message(STATUS "INC: ${INC}")

# Util
aux_source_directory(Util/MySqlRepository Util_SRC)
aux_source_directory(Util/Helper Util_SRC)
file(GLOB Util_INC "Util/MySqlRepository/*.h")
file(GLOB Util_INC "Util/Helper/*.h")

message(STATUS "Util_SRC: ${Util_SRC}")
message(STATUS "Util_INC: ${Util_INC}")

# 01 HomeMainWindow
aux_source_directory(Controller/01_HomeMainWindow 01_SRC)
aux_source_directory(Model/01_HomeMainWindow 01_SRC)
aux_source_directory(View/01_HomeMainWindow 01_SRC)
file(GLOB 01_INC "Model/01_HomeMainWindow/*.h" "View/01_HomeMainWindow/*.h")
file(GLOB 01_UI "View/01_HomeMainWindow/*.ui")

message(STATUS "01_SRC: ${01_SRC}")
message(STATUS "01_INC: ${01_INC}")
message(STATUS "01_UI: ${01_UI}")

list(APPEND CMAKE_AUTOUIC_SEARCH_PATHS "View/01_HomeMainWindow")

# 02 Login
aux_source_directory(Controller/02_Login 02_SRC)
aux_source_directory(Model/02_Login 02_SRC)
aux_source_directory(View/02_Login 02_SRC)
file(GLOB 02_INC "Model/02_Login/*.h" "View/02_Login/*.h")
file(GLOB 02_UI "View/02_Login/*.ui")

message(STATUS "02_SRC: ${02_SRC}")
message(STATUS "02_INC: ${02_INC}")
message(STATUS "02_UI: ${02_UI}")

list(APPEND CMAKE_AUTOUIC_SEARCH_PATHS "View/02_Login")

# 03 Device
aux_source_directory(Controller/03_Device 03_SRC)
aux_source_directory(Model/03_Device 03_SRC)
aux_source_directory(View/03_Device 03_SRC)
file(GLOB 03_INC "Model/03_Device/*.h" "View/03_Device/*.h")
file(GLOB 03_UI "View/03_Device/*.ui")

message(STATUS "03_SRC: ${03_SRC}")
message(STATUS "03_INC: ${03_INC}")
message(STATUS "03_UI: ${03_UI}")

list(APPEND CMAKE_AUTOUIC_SEARCH_PATHS "View/03_Device")

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
include_directories(
    "Controller"
    "Core"
    "Interface"
    "Patterns"
    "Model"
    "Util/MySqlRepository"
    "Util/Helper"

    "Controller/01_HomeMainWindow"
    "Model/01_HomeMainWindow"
    "View/01_HomeMainWindow"

    "Controller/02_Login"
    "Model/02_Login"
    "View/02_Login"

    "Controller/03_Device"
    "Model/03_Device"
    "View/03_Device"

    )

# 使用自动查找的存储的变量
add_executable(${PROJECT_NAME}
    "main.cpp"
    ${INC}
    ${SRC}
    ${UI}

    ${Util_INC}
    ${Util_SRC}
    ${Util_UI}

    ${01_INC}
    ${01_SRC}
    ${01_UI}

    ${02_INC}
    ${02_SRC}
    ${02_UI}

    ${03_INC}
    ${03_SRC}
    ${03_UI}
    )

target_include_directories(${PROJECT_NAME} PUBLIC $<TARGET_FILE_DIR:${PROJECT_NAME}>)

# 指定Qt依赖库和头文件
target_link_libraries(${PROJECT_NAME} Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
    Qt${QT_VERSION_MAJOR}::Multimedia
    Qt${QT_VERSION_MAJOR}::Charts
    Qt${QT_VERSION_MAJOR}::Sql
    )
