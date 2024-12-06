cmake_minimum_required(VERSION 3.20)
project(GateServer)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_PREFIX_PATH $ENV{MY_INSTALL_DIR})
if (NOT CMAKE_PREFIX_PATH)
    message(FATAL_ERROR "Please set CMAKE_PREFIX_PATH")
endif ()

# Boost
find_package(Boost REQUIRED COMPONENTS system filesystem CONFIG)

# MySQL
find_package(mysql-concpp CONFIG REQUIRED)
include_directories(${MYSQL_CONCPP_INCLUDE_DIR})
message(STATUS "Using mysql-concpp ${MYSQL_CONCPP_VERSION}")

find_package(PkgConfig REQUIRED)

# JsonCpp
#find_package(jsoncpp CONFIG REQUIRED)
#get_target_property(JSON_INC_PATH jsoncpp_object INTERFACE_INCLUDE_DIRECTORIES)
#include_directories(${JSON_INC_PATH})
pkg_check_modules(JSONCPP REQUIRED jsoncpp)
message(STATUS "Using JsonCpp ${JSONCPP_VERSION}")

# Redis
#find_package(hiredis CONFIG REQUIRED)
#include_directories(${hiredis_INCLUDE_DIRS})
pkg_check_modules(HIREDIS REQUIRED hiredis)
message(STATUS "Using hiredis ${HIREDIS_VERSION}")

# Protobuf
find_package(protobuf CONFIG REQUIRED)
message(STATUS "Using protobuf ${protobuf_VERSION}")
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
    MysqlDao.h
    message.grpc.pb.cc
    message.grpc.pb.h
    message.pb.cc
    message.pb.h
    VerifyGrpcClient.cpp
    VerifyGrpcClient.h
    StatusGrpcClient.cpp
    StatusGrpcClient.h)

add_executable(GateServer ${PROJECT_SRC})

# 解决报错：absl::lts_20240722::log_internal::LogMessage::operator<<(unsigned long)
target_compile_options(GateServer PRIVATE -fclang-abi-compat=17)

target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES} ${JSONCPP_LIBRARIES} ${HIREDIS_LIBRARIES} mysql::concpp mysql::concpp-jdbc protobuf::libprotobuf gRPC::grpc++_reflection gRPC::grpc++)
