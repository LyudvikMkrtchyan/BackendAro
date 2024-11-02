#include "../../includes/evants/complexOperationEvants.hpp"
#include <cppconn/prepared_statement.h>
#include <memory>
#include <nlohmann/json_fwd.hpp>

void theCarpetIsWashed(const request &req, response &res, DataBase &db){
    std::cout << "the Carpet is washed run" << std::endl;
    nlohmann::json json = nlohmann::json::parse(req.body());
    if(json["code"] != ""){
        std::cout << json.dump(4) << std::endl;
        int washerId = json["washerId"];
        double surface = json["surface"];
        std::string code = json["code"];
        int salary = db.getWorkerSalary(washerId);
        int amount = salary * surface;
    
        db.setTransactionWashFinance(washerId,amount,code);
        std::string statusClean = "clean";
        db.setCarpetStatus(code, statusClean);
        db.setCarpetWashDay(code);
    }
}
void changeTheCarpetStatusToDelivery(const request &req, response &res, DataBase &db){
    std::cout << "changeTheCarpetStatusToDelivery runned" << std::endl;
    nlohmann::json json =  nlohmann::json::parse(req.body());

    std::string carpetCode = json["code"];

    std::string carpetStatus = "read_for_delivery";

    db.setCarpetStatus(carpetCode, carpetStatus);
    db.setDeliveryDataTime(json);

}

void getCarpetsReadyForDelivery(const request &req, response &res, DataBase &db){
    std::cout << " getCarpetsReadyForDelivery is runned" << std::endl;
    nlohmann::json couriers = nlohmann::json::array();
    nlohmann::json carpets = nlohmann::json::array();
    
    couriers = db.getCouiriers();
    std::cout << "ok " << std::endl;
    carpets = db.getCarpetsReadyForDelivery();

    nlohmann::json answerJson;
    answerJson["worker"] = couriers;
    answerJson["carpet"] = carpets;
    
         if(!answerJson.empty()){
        res.result(boost::beast::http::status::ok);
    }else{
        res.result(boost::beast::http::status::unauthorized);
    }
    std::cout << answerJson.dump(4) << std::endl;
    res.set(boost::beast::http::field::content_type, "application/json");
    res.body() = answerJson.dump();
    
}
void changeCarpetsStatusToDelivered(const request& req, response& res , DataBase& db){
    nlohmann::json json = nlohmann::json::parse(req.body());
      std::vector<std::string> codes = json["codes"].get<std::vector<std::string>>();

    
    for (const auto& code : codes) {
        db.setCarpetStatusDelivered(code);

        double price = db.getCarpetPrice(code);

        db.carpetIsDeliveredFinances(code,price);
    }
}
void evantSwitchInitalaizComplexOperations(EvantSwitch& evantsMap){
    evantsMap.addEvant("/theCarpetIsWashed", theCarpetIsWashed);
    evantsMap.addEvant("/changeTheCarpetStatusToDelivery", changeTheCarpetStatusToDelivery);
    evantsMap.addEvant("/getCarpetsReadyForDelivery", getCarpetsReadyForDelivery);
     evantsMap.addEvant("/changeCarpetsStatusToDelivered", changeCarpetsStatusToDelivered);
}

