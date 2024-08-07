cmake_minimum_required(VERSION 3.20)
project(GateServer)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_PREFIX_PATH $ENV{MY_INSTALL_DIR} $ENV{MY_INSTALL_DIR}/grpc)
if (NOT CMAKE_PREFIX_PATH)
    message(FATAL_ERROR "Please set CMAKE_PREFIX_PATH")
endif ()

# Boost
find_package(Boost REQUIRED COMPONENTS system)

# MySQL
find_package(mysql-concpp CONFIG REQUIRED)
include_directories(${MYSQL_CONCPP_INCLUDE_DIR})
message(STATUS "Using MySQL Connector ${mysql-concpp_VERSION}")

# JsonCpp
find_package(jsoncpp CONFIG REQUIRED)
message(STATUS "Using JsonCpp ${jsoncpp_VERSION}")
get_target_property(JSON_INC_PATH jsoncpp_object INTERFACE_INCLUDE_DIRECTORIES)
include_directories(${JSON_INC_PATH})

# Redis
find_package(hiredis CONFIG REQUIRED)
include_directories(${hiredis_INCLUDE_DIRS})
message(STATUS "Using hiredis ${hiredis_VERSION}")

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
        MysqlDao.h
        message.grpc.pb.cc
        message.grpc.pb.h
        message.pb.cc
        message.pb.h)

add_executable(GateServer ${PROJECT_SRC})

target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES} ${hiredis_LIBRARIES} mysql::concpp protobuf::libprotobuf gRPC::grpc++_reflection gRPC::grpc++ jsoncpp_object)
