#pragma once

#include <functional>
#include <map>
#include "Singleton.h"
#include "const.h"

class HttpConnection;

typedef std::function<void(std::shared_ptr<HttpConnection>)> HttpHandler;

class LogicSystem : public Singleton<LogicSystem> {
    friend class Singleton<LogicSystem>;

public:
    ~LogicSystem();

    void RegGet(std::string url, HttpHandler handler);

    void RegPost(std::string url, HttpHandler handler);

    bool HandleGet(std::string path, std::shared_ptr<HttpConnection> con);

    bool HandlePost(std::string path, std::shared_ptr<HttpConnection> con);

private:
    LogicSystem();

    std::map<std::string, HttpHandler> _post_handlers;
    std::map<std::string, HttpHandler> _get_handlers;
};

