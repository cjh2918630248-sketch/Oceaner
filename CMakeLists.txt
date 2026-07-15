cmake_minimum_required(VERSION 3.10.0) #指定所需最低的cmake版本
project(Oceaner VERSION 0.1.0 LANGUAGES C CXX) #指定项目名以及编程语言

# 设置 C++ 标准为 C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON) # 强制使用指定版本

# raylib 路径
set(RAYLIB_DIR ${CMAKE_SOURCE_DIR}/3rdParty/raylib)

# pahomqtt 路径
set(PAHO_MQTT_DIR ${CMAKE_SOURCE_DIR}/3rdParty/paho.mqtt.cpp/build_sdk_debug)

add_executable(Oceaner src/main.cpp)

if(WIN32)
 target_compile_definitions(Oceaner PRIVATE PAHO_MQTTPP_IMPORTS PAHO_MQTT_IMPORTS)
endif()

target_include_directories(Oceaner PRIVATE
    ${RAYLIB_DIR}/include
    ${CMAKE_SOURCE_DIR}/3rdParty/nlohmann
    ${PAHO_MQTT_DIR}/include
)

target_link_directories(Oceaner PRIVATE
    ${RAYLIB_DIR}/lib
    ${PAHO_MQTT_DIR}/lib
)

if(WIN32)
    target_link_libraries(Oceaner PRIVATE 
        raylib
        winmm 
        gdi32 
        opengl32
    )
endif()