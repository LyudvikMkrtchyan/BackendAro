#include "../../../includes/evants/carpetsManipulation/carpetsManipulationSetters.hpp"
void setCarpetParametrFromWasher(const request& req, response& res , DataBase& db){
    nlohmann::json json = nlohmann::json::parse(req.body());
    std::string code = json["code"];
    std::string location = db.getCarpetLocation(code);
    int price = db.getPrice(location);
    
    json["price"] = price;
    
    db.setCarpetParametrFromWasher(json);
    



}
void setCarpetsCourier(const request& req, response& res , DataBase& db){
    std::cout << nlohmann::json::parse(req.body()).dump(4) << std::endl;
      nlohmann::json jsonObject = nlohmann::json::parse(req.body());

    std::vector<std::string> codes = jsonObject["codes"].get<std::vector<std::string>>();
   
    int workerId = jsonObject["worker"];

    for(std::string code : codes){
        db.setCarpetCouirier(code, workerId);
    }


}
void evantSwitchInitalaizCarpetsManipulationSetters(EvantSwitch& evantsMap){

    evantsMap.addEvant("/setCarpetParametrFromWasher", setCarpetParametrFromWasher);
    evantsMap.addEvant("/setCarpetsCourier", setCarpetsCourier);

}