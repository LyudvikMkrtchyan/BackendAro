#pragma once
#include "../time.hpp"
#include "carpetsGetters.hpp"
<<<<<<< HEAD
#include "carpetsGettersForAdmin.hpp"
=======
>>>>>>> f454e2f15b0011818af90f5d6e6a46eda2bd2d10
#include "carpetsSetters.hpp"
#include "carpetsSearchers.hpp" 
#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>

<<<<<<< HEAD
class Carpets:public CarpetsSetters
             ,public CarpetsGetters
             ,public CarpetsSearchers
             ,public CarpetsGettersForAdmin{
=======
class Carpets:public CarpetsSetters, public CarpetsGetters, public CarpetsSearchers{
>>>>>>> f454e2f15b0011818af90f5d6e6a46eda2bd2d10
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