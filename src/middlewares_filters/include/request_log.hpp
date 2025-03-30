#pragma once

#include <drogon/drogon.h>

#include <chrono>
#include <sstream>


class RequestLogger final : public drogon::HttpFilter<RequestLogger>
{
public:
    RequestLogger()
    {
        LOG_DEBUG << "Filter registered";
    }


    void doFilter(const drogon::HttpRequestPtr& req,
        drogon::FilterCallback&& fcb,
        drogon::FilterChainCallback&& fccb) override
    {
        LOG_DEBUG << get_log_data(req);
        fccb();
    }

private:
    static std::string get_log_data(const drogon::HttpRequestPtr &req)
    {
        auto addr = req->peerAddr().toIpPort();
        std::ostringstream ss;
        ss << "\n[RequestLogger]: " << get_current_datetime() << "\n";
        ss << "Address: " << addr  << "\n";
        ss << "Method: " << req->getMethodString() << "\n";
        ss << "Path: " << req->getPath() << "\n";

        auto query = req->query();
        ss << "Query: " << query << "\n";
        auto body = req->body();
        ss << "Body: " << body << "\n";
        return ss.str();
    }
    static std::string get_current_datetime()
    {
        const auto now = std::chrono::system_clock::now();
        const std::time_t now_c = std::chrono::system_clock::to_time_t(now);

        std::stringstream ss;
        ss << std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S");

        return ss.str();
    }
};
