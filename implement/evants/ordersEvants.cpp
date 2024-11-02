#include "../../includes/evants/ordersEvants.hpp"
#include <nlohmann/json_fwd.hpp>

void addOrder(const request& req, response& res , DataBase& db){
    std::cout <<  "add Order is runned" << std::endl;
    nlohmann::json json = nlohmann::json::parse(req.body());
    std::cout << json.dump(4) << std::endl;
    int carpetsCount = json["count"];
    std::string rowCode = json["code"];
    for(int i = 1; i <= carpetsCount; ++i){
        std::string code = rowCode + '/' + std::to_string(i);
        db.addNewOrder(json, code);
    }
}

void getOrders(const request& req, response& res , DataBase& db){
    std::cout << " getOrders is runned" << std::endl;
    nlohmann::json answerJson = nlohmann::json::array();

    answerJson = db.getOrders();

    if(!answerJson.empty()){
        res.result(boost::beast::http::status::ok);
    }else{
        res.result(boost::beast::http::status::unauthorized);
    }
    res.set(boost::beast::http::field::content_type, "application/json");
    res.body() = answerJson.dump();
}
void evantSwitchInitalaizOrders(EvantSwitch &evantsMap){
   evantsMap.addEvant("/addOrder", addOrder);
   evantsMap.addEvant("/getOrders", getOrders);
}