cmake_minimum_required(VERSION 3.20)
project(GateServer)

set(CMAKE_CXX_STANDARD 17)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
list(APPEND CMAKE_INSTALL_PATH $ENV{MY_INSTALL_DIR})

# MySQL
find_package(mysql-concpp REQUIRED)
include_directories(${CONCPP_INCLUDE_DIR})

# Boost
find_package(Boost REQUIRED COMPONENTS system)

# JsonCpp
find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
include_directories(${JSONCPP_INCLUDE_DIRS})

# Redis
pkg_check_modules(HIREDIS hiredis)
include_directories(${HIREDIS_INCLUDE_DIRS})

# Protobuf
find_package(Protobuf CONFIG REQUIRED)
message(STATUS "Using protobuf ${Protobuf_VERSION}")
# gRPC
find_package(gRPC CONFIG REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")

set(PROJECT_SRC GateServer.cpp
        const.h
        Singleton.h
        AsioIOServicePool.h
        AsioIOServicePool.cpp
        ConfigMgr.h
        ConfigMgr.cpp
        CServer.cpp
        CServer.h
        HttpConnection.cpp
        HttpConnection.h
        LogicSystem.cpp
        LogicSystem.h
        RedisMgr.cpp
        RedisMgr.h
        MysqlMgr.cpp
        MysqlMgr.h
        MysqlDao.cpp
        MysqlDao.h)

add_executable(GateServer ${PROJECT_SRC})

target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES} ${HIREDIS_LIBRARIES} MySQL::conncpp protobuf::libprotobuf gRPC::grpc++_reflection gRPC::grpc++)
