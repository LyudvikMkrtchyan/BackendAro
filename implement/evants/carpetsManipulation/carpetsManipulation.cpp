#include "../../../includes/evants/carpetsManipulation/carpetsManipulation.hpp"
#include <boost/beast/http/status.hpp>
#include <nlohmann/json_fwd.hpp>

void addCarpet(const request& req, response& res , DataBase& db){
    std::cout << "add New Product is runed" << std::endl;
    nlohmann::json json = json.parse(req.body());

    db.addCarpet(json); 
}




void changeCarpetInfo(const request& req, response& res , DataBase& db){
    nlohmann::json json = nlohmann::json::parse(req.body());

    db.changeCarpetInfo(json);
}
void evantSwitchInitalaizProductManipulation(EvantSwitch& evantsMap){
    evantsMap.addEvant("/addCarpet", addCarpet);
    evantsMap.addEvant("/getHeavyBurden", getHeavyBurden);
 
    evantsMap.addEvant("/changeCarpetInfo", changeCarpetInfo);
  
}