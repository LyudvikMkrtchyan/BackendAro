#pragma once
#include "../time.hpp"
#include "carpetsSetters.hpp"
#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
struct DeliveryAddresContent{
    DeliveryAddresContent();
    std::string address;
    std::string entrance; 
    std::string floor; 
    std::string flat;
    std::string phone_number; 
    std::string delivery_time_min; 
    std::string delivery_time_max;
    int carpetsCount;
    double totalSurface; 
    double totalPrice; 
    nlohmann::json to_json();
};
class CarpetsGetters{
public:
    CarpetsGetters(sql::Connection* connection);
public:
    
    nlohmann::json getCarpets();
    nlohmann::json getWashedCarpets();
    nlohmann::json getDeliveredCarpets(std::string startDate, std::string endDate);
    nlohmann::json getCarpetInfo(std::string code);
    nlohmann::json getCarpetsForWash(int duringTime);
    nlohmann::json getCarpetsReadyForDelivery();
    nlohmann::json getHeavyBurden(std::string date);
    nlohmann::json getActualCarpetForWasher(int washerId);
    std::string getCarpetLocation(std::string code);
    nlohmann::json getCarpetForDeliveriConcretWorker(int workerId);
<<<<<<< HEAD
    nlohmann::json getWashedCarpetsWithDay(std::string day);
=======
    nlohmann::json getTodaysWashedCarpets();
>>>>>>> f454e2f15b0011818af90f5d6e6a46eda2bd2d10
    nlohmann::json getInDeliveredCarpetsFullInfoFromAddress(nlohmann::json& json);
    double getCarpetPrice(std::string code);


private:
    nlohmann::json extractCarpets(std::shared_ptr<sql::ResultSet> );
    Time* time;
private:
    sql::Connection* connection;
};