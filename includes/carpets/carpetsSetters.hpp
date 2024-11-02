#pragma once
#include "../time.hpp"
#include <mysql/mysql.h> 
#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>

class CarpetsSetters{
public:
    CarpetsSetters(sql::Connection* connection);
public:
    void addCarpet(nlohmann::json& json);
    void setCarpetParametrFromWasher(nlohmann::json& json);
    void setCarpetStatusDelivered(std::string code);
    void setCarpetStatus(std::string carpetCode, std::string carpetStatus);
    void setCarpetStatusReadyFormDelivery(std::string carpetCode);
    void setCarpetWashDay(std::string carpetCode);
    void setCarpetsParametrsForDelivery(nlohmann::json& json);
    void setDeliveryDataTime(nlohmann::json& json);
    void setCarpetCouirier(std::string carpetsCode, int courierId);

private:
    Time* time;
private:
    sql::Connection* connection;
};