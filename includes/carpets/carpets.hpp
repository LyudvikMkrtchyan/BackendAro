#pragma once
#include "../time.hpp"
#include "carpetsGetters.hpp"

#include "carpetsGettersForAdmin.hpp"
#include "carpetsSetters.hpp"
#include "carpetsSearchers.hpp" 
#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>


class Carpets:public CarpetsSetters
             ,public CarpetsGetters
             ,public CarpetsSearchers
             ,public CarpetsGettersForAdmin{

public:
    Carpets(sql::Connection* connection);
public:
    
    nlohmann::json searchCarpetWithStatus(std::string status);
    nlohmann::json searchWithPhoneNumber(std::string phoneNumber);
    nlohmann::json searchWithAddress(std::string address);
    nlohmann::json searchWithCode(std::string code);

    void changeCarpetInfo(nlohmann::json& json);

private:
    Time* time;
private:
    sql::Connection* connection;
};