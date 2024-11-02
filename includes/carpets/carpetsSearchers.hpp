
#pragma once
#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>

class CarpetsSearchers{
public:
    CarpetsSearchers(sql::Connection* connection);
public:
    
    nlohmann::json searchCarpetsWithStatus(std::string status);
    nlohmann::json searchCarpetsWithPhoneNumber(std::string phoneNumber);
    nlohmann::json searchCarpetsWithAddress(std::string address);
    nlohmann::json searchCarpetsWithCode(std::string code);

    void changeCarpetInfo(nlohmann::json& json);

private:
private:
    sql::Connection* connection;
};