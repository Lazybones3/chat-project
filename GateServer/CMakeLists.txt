cmake_minimum_required(VERSION 3.20)
project(GateServer)

set(CMAKE_CXX_STANDARD 11)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# Boost
find_package(Boost REQUIRED COMPONENTS system)

# JsonCpp
find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
include_directories(${JSONCPP_INCLUDE_DIRS})

# Redis
pkg_check_modules(HIREDIS hiredis)
include_directories(${HIREDIS_INCLUDE_DIRS})

# MySQL
find_package(mysql-concpp REQUIRED)
include_directories(${CONCPP_INCLUDE_DIR})

set(PROJECT_SRC GateServer.cpp const.h Singleton.h)

add_executable(GateServer ${PROJECT_SRC})

target_link_libraries(GateServer PRIVATE ${Boost_LIBRARIES} ${HIREDIS_LIBRARIES} MySQL::conncpp)
