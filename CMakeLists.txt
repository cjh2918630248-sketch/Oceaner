cmake_minimum_required(VERSION 3.10.0) #指定所需最低的cmake版本
project(Oceaner VERSION 0.1.0 LANGUAGES C CXX) #指定项目名以及编程语言

# 设置 C++ 标准为 C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON) # 强制使用指定版本

# raylib 路径
set(RAYLIB_DIR ${CMAKE_SOURCE_DIR}/3rdParty/raylib)
# pahomqtt 路径
set(PAHO_MQTT_DIR ${CMAKE_SOURCE_DIR}/3rdParty/paho.mqtt.cpp/build_sdk_debug)
# raylib-tmx 路径
set(RAYLIB_TMX_DIR ${CMAKE_SOURCE_DIR}/3rdParty/raylib-tmx)
# tmx 路径
set(TMX_DIR ${CMAKE_SOURCE_DIR}/3rdParty/tmx)
# libxml2 路径
set(LIBXML2_DIR ${CMAKE_SOURCE_DIR}/3rdParty/libxml2)
# zlib 路径
set(ZLIB_DIR ${CMAKE_SOURCE_DIR}/3rdParty/zlib)
# iconv 路径
set(ICONV_DIR ${CMAKE_SOURCE_DIR}/3rdParty/iconv)



add_executable(Oceaner src/main.cpp)

if(WIN32)
 target_compile_definitions(Oceaner PRIVATE PAHO_MQTTPP_IMPORTS PAHO_MQTT_IMPORTS)
endif()

target_include_directories(Oceaner PRIVATE
    ${RAYLIB_DIR}/include
    ${CMAKE_SOURCE_DIR}/3rdParty/nlohmann
    ${PAHO_MQTT_DIR}/include
    ${RAYLIB_TMX_DIR}/include
    ${TMX_DIR}/include
    ${LIBXML2_DIR}/include
    ${ZLIB_DIR}/include
    ${ICONV_DIR}/include
)

target_link_directories(Oceaner PRIVATE
    ${RAYLIB_DIR}/lib
    ${PAHO_MQTT_DIR}/lib
    ${RAYLIB_TMX_DIR}/lib
    ${TMX_DIR}/lib
    ${LIBXML2_DIR}/lib
    ${ZLIB_DIR}/lib
    ${ICONV_DIR}/lib
)

if(WIN32)
    target_link_libraries(Oceaner PRIVATE 
        ${RAYLIB_TMX_DIR}/lib/libraylib-tmx.a
        raylib
        ${TMX_DIR}/lib/libtmx.a
        ${LIBXML2_DIR}/lib/libxml2.dll.a
        ${ICONV_DIR}/lib/libiconv.dll.a
        winmm 
        gdi32 
        opengl32
    )
endif()