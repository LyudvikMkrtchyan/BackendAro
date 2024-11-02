#include "../../includes/carpets/carpetsGettersForAdmin.hpp"
#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <memory>
#include <unordered_map>

CarpetsGettersForAdmin::CarpetsGettersForAdmin(sql::Connection* conn): connection(conn){};

nlohmann::json CarpetsGettersForAdmin::getIntervalWashedCarpets(nlohmann::json& json){
    std::string startDate = json["startDate"];
    std::string endDate = json["endDate"];
    std::map<std::string,DayWashedCarpet> washedCarpetWithDays;
    std::cout << startDate << std::endl;
    std::cout << endDate << std::endl;
    std::unique_ptr<sql::PreparedStatement> pstmp(connection->prepareStatement(R"(
        SELECT surface, price, wash_date FROM Carpets
        WHERE wash_date >=? and wash_date <= ?
    )"));
    pstmp->setDateTime(1, startDate);
    pstmp->setDateTime(2, endDate);
    std::unique_ptr<sql::ResultSet> res(pstmp->executeQuery());
    while(res->next()){
        std::string washDate = res->getString("wash_date");
        double price         = res->getDouble("price");
        double surface         = res->getDouble("surface");

        auto DaysWashedInfo = washedCarpetWithDays.find(washDate);

        if(DaysWashedInfo != washedCarpetWithDays.end()){
            DaysWashedInfo->second.dayTotalPrice += price;
            DaysWashedInfo->second.dayTotalSurface += surface;
            DaysWashedInfo->second.count ++;
        }else{
            washedCarpetWithDays[washDate].dayTotalPrice = price;
            washedCarpetWithDays[washDate].dayTotalSurface = surface;
            washedCarpetWithDays[washDate].count = 1;
        }
    }
    
    nlohmann::json daysInfo = nlohmann::json::array();
    double totalPrice   = 0;
    double totalSurface = 0;
    int totalCount      = 0;
    for(auto dayInfo : washedCarpetWithDays){
        nlohmann::json tmpDayInfo;
         
        tmpDayInfo["washDay"]    = dayInfo.first;
        tmpDayInfo["totalPrice"] = dayInfo.second.dayTotalPrice;
        tmpDayInfo["totalSurface"] = dayInfo.second.dayTotalSurface;
        tmpDayInfo["count"] = dayInfo.second.count;
        
        totalPrice += dayInfo.second.dayTotalPrice;    
        totalSurface += dayInfo.second.dayTotalSurface;
        totalCount += dayInfo.second.count;
        daysInfo.push_back(tmpDayInfo);
    }

    nlohmann::json answerJson;
    answerJson["date"] = daysInfo;
    answerJson["totalPrice"] = totalPrice;
    answerJson["totalSurface"] = totalSurface;
    answerJson["totalCount"] = totalCount;

    return answerJson;
}
nlohmann::json CarpetsGettersForAdmin::getIntervalDeliveredCarpets(nlohmann::json& json){
    std::string startDate = json["startDate"];
    std::string endDate = json["endDate"];
    std::map<std::string,DayWashedCarpet> washedCarpetWithDays;
    std::cout << startDate << std::endl;
    std::cout << endDate << std::endl;
    std::unique_ptr<sql::PreparedStatement> pstmp(connection->prepareStatement(R"(
        SELECT surface, price, delivery_date FROM Carpets
        WHERE delivery_date >=? and delivery_date <= ?
    )"));
    pstmp->setDateTime(1, startDate);
    pstmp->setDateTime(2, endDate);
    std::unique_ptr<sql::ResultSet> res(pstmp->executeQuery());
    while(res->next()){
        std::string washDate = res->getString("delivery_date");
        double price         = res->getDouble("price");
        double surface         = res->getDouble("surface");

        auto DaysWashedInfo = washedCarpetWithDays.find(washDate);

        if(DaysWashedInfo != washedCarpetWithDays.end()){
            DaysWashedInfo->second.dayTotalPrice += price;
            DaysWashedInfo->second.dayTotalSurface += surface;
            DaysWashedInfo->second.count ++;
        }else{
            washedCarpetWithDays[washDate].dayTotalPrice = price;
            washedCarpetWithDays[washDate].dayTotalSurface = surface;
            washedCarpetWithDays[washDate].count = 1;
        }
    }
    
    nlohmann::json daysInfo = nlohmann::json::array();
    double totalPrice   = 0;
    double totalSurface = 0;
    int totalCount      = 0;
    for(auto dayInfo : washedCarpetWithDays){
        nlohmann::json tmpDayInfo;
         
        tmpDayInfo["deliveryDate"]    = dayInfo.first;
        tmpDayInfo["totalPrice"] = dayInfo.second.dayTotalPrice;
        tmpDayInfo["totalSurface"] = dayInfo.second.dayTotalSurface;
        tmpDayInfo["count"] = dayInfo.second.count;
        
        totalPrice += dayInfo.second.dayTotalPrice;    
        totalSurface += dayInfo.second.dayTotalSurface;
        totalCount += dayInfo.second.count;
        daysInfo.push_back(tmpDayInfo);
    }

    nlohmann::json answerJson;
    answerJson["date"] = daysInfo;
    answerJson["totalPrice"] = totalPrice;
    answerJson["totalSurface"] = totalSurface;
    answerJson["totalCount"] = totalCount;

    return answerJson;
}

