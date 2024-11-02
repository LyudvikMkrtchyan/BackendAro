#include "../../../includes/evants/carpetsManipulation/carpetsManipulationGetters.hpp"

void getCarpets(const request& req, response& res , DataBase& db){
    std::cout << "get Carpetsis runed" << std::endl;
    nlohmann::json json = json.parse(req.body());
    nlohmann::json answerJson;
    answerJson =  db.getCarpets();
    
    if(!answerJson.empty()){
        res.result(boost::beast::http::status::ok);
    }else{
        res.result(boost::beast::http::status::unauthorized);
    }
    res.set(boost::beast::http::field::content_type, "application/json");
    res.body() = answerJson.dump();
}
void getWashedCarpets(const request& req, response& res , DataBase& db){
    std::cout << "get Washed Carpetsis runed" << std::endl;;
    nlohmann::json answerJson;
    answerJson =  db.getWashedCarpets();
    
    if(!answerJson.empty()){
        res.result(boost::beast::http::status::ok);
    }else{
        res.result(boost::beast::http::status::unauthorized);
    }
    res.set(boost::beast::http::field::content_type, "application/json");
    std::cout << answerJson.dump(4) << std::endl;
    res.body() = answerJson.dump();
}
void getTodayWashedCarpets(const request& req, response& res , DataBase& db){
    std::cout << "Get todays Washed Carpets is runned" << std::endl;
    nlohmann::json answerJson;

    std::string todayDate = Time().getTodaysDate();
    answerJson = db.getWashedCarpetsWithDay(todayDate);


   
    if(!answerJson.empty()){
        res.result(boost::beast::http::status::ok);
    }else{
        res.result(boost::beast::http::status::unauthorized);
    }
    res.set(boost::beast::http::field::content_type, "application/json");
    res.body() = answerJson.dump();



}
void getTodayDeliveredCarpets(const request& req, response& res , DataBase& db){
    nlohmann::json answerJson;
    std::string todayDate = Time().getTodaysDate();
    
    answerJson = db.getDeliveredCarpets(todayDate, todayDate);
    
    if(!answerJson.empty()){
        res.result(boost::beast::http::status::ok);
    }else{
        res.result(boost::beast::http::status::unauthorized);
    }
    res.set(boost::beast::http::field::content_type, "application/json");
    std::cout << answerJson.dump(4) << std::endl;
    res.body() = answerJson.dump();
}


void prepareCarpetForDelivery(const request& req, response& res , DataBase& db){
    std::cout << "prepareCarpetForDelivery is runned" << std::endl;
    nlohmann::json json = nlohmann::json::parse(req.body());
    db.setCarpetsParametrsForDelivery(json);
}


void getActualCarpetForWasher(const request& req, response& res , DataBase& db){
    std::cout << "get Actual Carpet For Washer is runed" << std::endl;

    nlohmann::json json = nlohmann::json::parse(req.body());
    nlohmann::json answer;
    
    int washerId = json["washerId"];

    answer = db.getActualCarpetForWasher(washerId);
    if(!answer.empty()){
        res.result(boost::beast::http::status::ok);
    }else{
        res.result(boost::beast::http::status::unauthorized);
    }
    res.set(boost::beast::http::field::content_type, "application/json");
    res.body() = answer.dump();

}
void getCarpetInfo(const request& req, response& res , DataBase& db){
    nlohmann::json answerJson;
    std::string carpetCode = nlohmann::json::parse(req.body())["code"];

    answerJson = db.getCarpetInfo(carpetCode); 
    if(!answerJson.empty()){
        res.result(boost::beast::http::status::ok);
    }else{
        res.result(boost::beast::http::status::unauthorized);
    }
    res.set(boost::beast::http::field::content_type, "application/json");
    res.body() = answerJson.dump();
    
}
void getCarpetsForWash(const request& req, response& res , DataBase& db){
    nlohmann::json answerJson = nlohmann::json::array();
    int duringTIme = db.getDuringTime();

    answerJson = db.getCarpetsForWash(duringTIme);

    if(!answerJson.empty()){
        res.result(boost::beast::http::status::ok);
    }else{
        res.result(boost::beast::http::status::unauthorized);
    }
    res.set(boost::beast::http::field::content_type, "application/json");
    res.body() = answerJson.dump();
    std::cout << answerJson.dump(4) << std::endl;
}

void getCarpetForDeliveriConcretWorker(const request& req, response& res , DataBase& db){
    std::cout <<  "getCarpetForDeliveriConcretWorker is runned" << std::endl;
    nlohmann::json json = nlohmann::json::parse(req.body());
    int workerId =  json["id"];
    nlohmann::json addressCards = nlohmann::json::array();
    addressCards = db.getCarpetForDeliveriConcretWorker(workerId);

    double totalPrice = 0;
    double totalSurface = 0;
    for(auto address : addressCards){
        totalPrice += address["totalPrice"].get<double>();
        totalSurface += address["totalSurface"].get<double>();
    }
    nlohmann::json answerJson ;
    answerJson["totalPrice"] = totalPrice;
    answerJson["totalSurface"] = totalSurface;
    answerJson["addressCards"] = addressCards;
    
    
     
    res.result(boost::beast::http::status::ok);
    res.set(boost::beast::http::field::content_type, "application/json");
    std::cout << answerJson.dump(4) << std::endl;
    res.body() = answerJson.dump();

}
void getInDeliveredCarpetsFullInfoFromAddress(const request& req, response& res , DataBase& db){
    std::cout <<  "getCarpetsFullInfoFromAddress is runned" << std::endl;
    nlohmann::json json = nlohmann::json::parse(req.body());

    nlohmann::json answerJson = nlohmann::json::array();

    answerJson = db.getInDeliveredCarpetsFullInfoFromAddress(json);

    if(!answerJson.empty()){
        res.result(boost::beast::http::status::ok);
    }else{
        res.result(boost::beast::http::status::unauthorized);
    }
    res.set(boost::beast::http::field::content_type, "application/json");
    res.body() = answerJson.dump();
    std::cout << answerJson.dump(4) << std::endl;

}


void getHeavyBurden(const request& req, response& res , DataBase& db){
     std::cout << "geatHeavyBurden  is runed" << std::endl;
    nlohmann::json json = json.parse(req.body());
    std::string date = json["date"];  
    
     nlohmann::json answerJson;
    answerJson =  db.getHeavyBurden(date);

     if(!answerJson.empty()){
        res.result(boost::beast::http::status::ok);
    }else{
        res.result(boost::beast::http::status::unauthorized);
    }
    res.set(boost::beast::http::field::content_type, "application/json");
    res.body() = answerJson.dump();

}
void evantSwitchInitalaizCarpetsManipulationGetters(EvantSwitch& evantsMap){
    evantsMap.addEvant("/getCarpets", getCarpets);
    evantsMap.addEvant("/getWashedCarpets", getWashedCarpets);
    evantsMap.addEvant("/getTodayDeliveredCarpets", getTodayDeliveredCarpets);
    evantsMap.addEvant("/getActualCarpetForWasher", getActualCarpetForWasher);
    evantsMap.addEvant("/getCarpetInfo", getCarpetInfo);
    evantsMap.addEvant("/getCarpetsForWash", getCarpetsForWash);
    evantsMap.addEvant("/prepareCarpetForDelivery", prepareCarpetForDelivery);
    evantsMap.addEvant("/getTodayWashedCarpets", getTodayWashedCarpets);
    evantsMap.addEvant("/getCarpetForDeliveriConcretWorker", getCarpetForDeliveriConcretWorker);
    evantsMap.addEvant("/getInDeliveredCarpetsFullInfoFromAddress", getInDeliveredCarpetsFullInfoFromAddress);

}
