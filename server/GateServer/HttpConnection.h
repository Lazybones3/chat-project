#pragma once

#include "const.h"

class HttpConnection : public std::enable_shared_from_this<HttpConnection> {
    // 为防止互相引用，以及LogicSystem能够成功访问HttpConnection：
    // 1.在LogicSystem.cpp中包含HttpConnection.h头文件
    // 2.在HttpConnection.cpp中包含LogicSystem.h头文件，并且在HttpConnection中添加友元类LogicSystem
    friend class LogicSystem;

public:
    HttpConnection(boost::asio::io_context &ioc);

    void Start();

    // 参数解析
    void PreParseGetParam();

    tcp::socket &GetSocket() {
        return _socket;
    }

private:
    void CheckDeadline();

    void WriteResponse();

    void HandleReq();

    tcp::socket _socket;
    // _buffer用来接收数据
    beast::flat_buffer _buffer{8192};
    //_request用来解析请求
    http::request<http::dynamic_body> _request;
    // _response用来回应客户端
    http::response<http::dynamic_body> _response;
    // deadline_用来做定时器判断请求是否超时
    net::steady_timer deadline_{_socket.get_executor(), std::chrono::seconds(60)};

    std::string _get_url;
    std::unordered_map<std::string, std::string> _get_params;
};

