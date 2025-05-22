#pragma once

#include "idbrepository.hpp"
#include "mongo_dbrepository.hpp"

#include <drogon/drogon.h>

class DBContext : public drogon::Plugin<DBContext>
{
public:
    DBContext()
    {

    }

    void initAndStart(const Json::Value& config) override {
        mDBContext = std::make_shared<MongoDBRepository>(config["uri"].asString(), config["database"].asString());
    }

    void shutdown() override {}

    std::shared_ptr<IDBRepository> getService() {
        return mDBContext;
    }

private:
    std::shared_ptr<IDBRepository> mDBContext;
};