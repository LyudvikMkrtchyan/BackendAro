#include "../../../includes/evants/carpetsManipulation/carpetsManipulationGettersForAdmin.hpp"


void getIntervalWashedCarpets(const request& req, response& res , DataBase& db){
    std::cout << "Get Interval Washed Carpets is runned" << std::endl;
    nlohmann::json json = nlohmann::json::parse(req.body());
    nlohmann::json answerJson;

    answerJson = db.getIntervalWashedCarpets(json);

    if(!answerJson.empty()){
        res.result(boost::beast::http::status::ok);
    }else{
        res.result(boost::beast::http::status::unauthorized);
    }
    res.set(boost::beast::http::field::content_type, "application/json");
    std::cout << answerJson.dump(4) << std::endl;
    res.body() = answerJson.dump();
}
void getIntervalDeliveredCarpets(const request& req, response& res , DataBase& db){
    std::cout << "Get Interval Washed Carpets is runned" << std::endl;
    nlohmann::json json = nlohmann::json::parse(req.body());
    nlohmann::json answerJson;

    answerJson = db.getIntervalDeliveredCarpets(json);

    if(!answerJson.empty()){
        res.result(boost::beast::http::status::ok);
    }else{
        res.result(boost::beast::http::status::unauthorized);
    }
    res.set(boost::beast::http::field::content_type, "application/json");
    std::cout << answerJson.dump(4) << std::endl;
    res.body() = answerJson.dump();
}
void getConcretDayWashedCarpets(const request& req, response& res , DataBase& db){
    nlohmann::json json = nlohmann::json::parse(req.body());
    nlohmann::json answerJson;

    std::string washDate = json["washDate"];

    answerJson = db.getWashedCarpetsWithDay(washDate);

    if(!answerJson.empty()){
        res.result(boost::beast::http::status::ok);
    }else{
        res.result(boost::beast::http::status::unauthorized);
    }
    res.set(boost::beast::http::field::content_type, "application/json");
    std::cout << answerJson.dump(4) << std::endl;
    res.body() = answerJson.dump();
}



void evantSwitchInitalaizCarpetsManipulationGettersForAdmin(EvantSwitch& evantsMap){
    evantsMap.addEvant("/getIntervalWashedCarpets", getIntervalWashedCarpets);
    evantsMap.addEvant("/getIntervalDeliveredCarpets", getIntervalDeliveredCarpets);
    evantsMap.addEvant("/getConcretDayWashedCarpets", getConcretDayWashedCarpets);

}
