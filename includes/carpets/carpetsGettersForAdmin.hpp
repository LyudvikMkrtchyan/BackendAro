#pragma once
#include "../time.hpp"
#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
struct DayWashedCarpet{
    double dayTotalPrice;
    double dayTotalSurface;
    int count;
};
class CarpetsGettersForAdmin{
public:
    CarpetsGettersForAdmin(sql::Connection* connection);

    nlohmann::json getIntervalWashedCarpets(nlohmann::json& json);
    nlohmann::json getIntervalDeliveredCarpets(nlohmann::json& json);
    nlohmann::json getConcretDayWashedCarpets(nlohmann::json& json);
public:
    
  


private:
    Time* time;
private:
    sql::Connection* connection;
};