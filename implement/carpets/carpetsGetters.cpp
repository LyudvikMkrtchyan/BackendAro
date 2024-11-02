#include "../../includes/carpets/carpetsGetters.hpp"
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <memory>
#include <unordered_map>

DeliveryAddresContent::DeliveryAddresContent():address(""), entrance(""), floor(""), flat(""), phone_number(""),
          delivery_time_min(""), delivery_time_max(""),
          totalSurface(0.0), totalPrice(0.0), carpetsCount(0) {}
nlohmann::json DeliveryAddresContent::to_json(){

        nlohmann::json answer = {
            {"address", address},
            {"entrance", entrance},
            {"floor", floor},
            {"flat", flat},
            {"phone_number", phone_number},
            {"delivery_time_min", delivery_time_min},
            {"delivery_time_max", delivery_time_max},
            {"totalSurface", totalSurface},
            {"totalPrice", totalPrice},
            {"carpetsCount", carpetsCount}
        };
        return answer; 
    
};

CarpetsGetters::CarpetsGetters(sql::Connection* conn):connection(conn){}
nlohmann::json CarpetsGetters::getCarpets(){
    std::cout << "Carpets::getCarpets is runned" << std::endl;
    std::unique_ptr<sql::Statement> stmt(connection->createStatement());
    
    std::shared_ptr<sql::ResultSet> res(stmt->executeQuery(
        R"(SELECT address, phone_number, pickup_date, desired_date, status, code 
           FROM Carpets 
           ORDER BY desired_date ASC)"));
    
    return extractCarpets(res);
}
nlohmann::json CarpetsGetters::getWashedCarpets(){
    nlohmann::json answerJson = nlohmann::json::array();
    std::cout << "Carpets::getWashedCarpets is runned" << std::endl;
    std::unique_ptr<sql::Statement> stmt(connection->createStatement());
    
    std::shared_ptr<sql::ResultSet> res(stmt->executeQuery(
        R"(SELECT wash_date, desired_date, phone_number, address, surface, price, code 
           FROM Carpets Where status='clean'
           ORDER BY wash_date ASC)"));
    
    while(res->next()){
        nlohmann::json tmp;

        tmp["washedDate"] = res->getString("wash_date");
        tmp["desiredDate"] = res->getString("desired_date");  
        tmp["phoneNumber"] = res->getString("phone_number");
        tmp["address"] = res->getString("address");
        tmp["surface"] = res->getString("surface");
        tmp["price"] = res->getString("price");
        tmp["code"] = res->getString("code"); 
    
        answerJson.push_back(tmp);
    }

    return answerJson;
}
nlohmann::json CarpetsGetters::getDeliveredCarpets(std::string startDate, std::string endDate){
    nlohmann::json carpetsArray = nlohmann::json::array();
    nlohmann::json answerJson;

    double totalPrice = 0;
    double totalSurface = 0;
    int totalCount = 0;
    
    std::unique_ptr<sql::PreparedStatement> pstmp(connection->prepareStatement(R"(
        SELECT price, surface, delivery_date, code
        FROM Carpets
        WHERE delivery_date >= ? and delivery_date <= ?
    
    )"));

    pstmp->setString(1, startDate);
    pstmp->setString(2, endDate);

    std::unique_ptr<sql::ResultSet> res(pstmp->executeQuery());

    while(res->next()){
        std::string deliveredDate = res->getString("delivery_date");
        double surface            = res->getDouble("surface");
        double price            = res->getDouble("price");
        std::string code = res->getString("code");

        nlohmann::json tmpCarpet;

        tmpCarpet["surface"] = surface;
        tmpCarpet["price"] = price;
        tmpCarpet["code"] = code;

        totalCount++;
        totalPrice   += price;
        totalSurface += surface;

        carpetsArray.push_back(tmpCarpet);
    }

    answerJson["totalSurface"] = totalSurface;
    answerJson["totalCount"] = totalCount;
    answerJson["totalPrice"] = totalPrice;
    answerJson["date"] = carpetsArray;

    return answerJson;
}
nlohmann::json CarpetsGetters::getCarpetInfo(std::string code){
    std::cout << "get Carpet info is runned" << std::endl;
    nlohmann::json answer;
    std::unique_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement("Select * From Carpets Where code=?;"));
    pstmt->setString(1, code);

    sql::ResultSet* res = pstmt->executeQuery();

    if(res->next()){
         answer["id"] = res->getInt("id");
        answer["address"] = res->getString("address");
        answer["entrance"] = res->getString("entrance");
        answer["phone_number"] = res->getString("phone_number");
        answer["floor"] = res->getString("floor");
        answer["flat"] = res->getString("flat");
        answer["pickup_date"] = res->getString("pickup_date");
        answer["id_delivery_to_washing"] = res->getInt("id_delivery_to_washing");
        answer["id_delivery_to_home"] = res->getInt("id_delivery_to_home");
        answer["wash_date"] = res->getString("wash_date");
        answer["delivery_date"] = res->getString("delivery_date");
        answer["washer"] = res->getInt("washer");
        answer["surface"] = res->getDouble("surface");
        answer["price"] = res->getDouble("price");
        answer["status"] = res->getString("status");
        answer["code"] = res->getString("code");
        answer["desired_date"] = res->getString("desired_date");
        answer["location"] = res->getString("location");
    }
    std::cout << answer.dump(4) << std::endl;
    return answer;
}
nlohmann::json CarpetsGetters::getCarpetsForWash(int duringTIme){
    nlohmann::json answerJson = nlohmann::json::array();

    std::string dateToday = time->getTodaysDate();

    std::string highDate = time->addDaysToDate(dateToday, duringTIme);

    sql::PreparedStatement* pstmp = connection->prepareStatement(R"(Select address, code, desired_date 
                                                                        From Carpets 
                                                                        where desired_date<=? and status='dirty')");
    pstmp->setString(1, highDate);
    sql::ResultSet* res = pstmp->executeQuery();

    while(res->next()){
        std::string desired_date = res->getString("desired_date");
        std::string washDate = Time().addDaysToDate(desired_date, -(duringTIme));
        std::string address = res->getString("address");
        std::string code = res->getString("code");

        nlohmann::json tmp;
        tmp["washDate"] = washDate;
        tmp["address"]      = address;
        tmp["code"]         = code;

        answerJson.push_back(tmp);
    }

    return answerJson;
    
}
nlohmann::json CarpetsGetters::getActualCarpetForWasher(int washeId){
    nlohmann::json answer;
    sql::PreparedStatement* pstmt = connection->prepareStatement("Select code, surface From Carpets Where status='washing' and washer=?;");
    pstmt->setInt(1, washeId);
    sql::ResultSet* res = pstmt->executeQuery();
    if(res->next()){
        answer["code"] = res->getString("code");
        answer["surface"] = res->getDouble("surface");
    }
    return answer;
    
}
std::string CarpetsGetters::getCarpetLocation(std::string code){
    std::string location;
    sql::PreparedStatement* pstmt = connection->prepareStatement("Select location From Carpets Where code=?;");
    pstmt->setString(1, code);
    sql::ResultSet* res = pstmt->executeQuery();

    if(res->next()){
        location = res->getString("location");
    }
    return location;
}

nlohmann::json CarpetsGetters::getCarpetsReadyForDelivery(){
    nlohmann::json answerJson = nlohmann::json::array();
    std::cout << "Carpets::getWashedCarpets is runned" << std::endl;
    std::unique_ptr<sql::Statement> stmt(connection->createStatement());
    
    std::shared_ptr<sql::ResultSet> res(stmt->executeQuery(
        R"(Select wash_date, desired_date, delivery_time_min, delivery_time_max, surface, price, code
                From Carpets
                Where status = 'read_for_delivery')"));
    
    while(res->next()){
        nlohmann::json tmp;

        tmp["wash_date"] = res->getString("wash_date");
        tmp["desired_date"] = res->getString("desired_date");
        tmp["delivery_time_min"] = res->getString("delivery_time_min");
        tmp["delivery_time_max"] = res->getString("delivery_time_max");  
        tmp["surface"] = res->getString("surface");
        tmp["price"] = res->getString("price");
        tmp["code"] = res->getString("code"); 
    
        answerJson.push_back(tmp);
    }

    return answerJson; 
}
nlohmann::json CarpetsGetters::getHeavyBurden(std::string date){
    std::string endDate = time->addDaysToDate(date, 15);

    nlohmann::json answerJson = nlohmann::json::array();
    std::unique_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement(R"(SELECT desired_date, COUNT(*) AS product_count
                                                FROM Carpets
                                                WHERE desired_date BETWEEN ? AND ?
                                                GROUP BY desired_date
                                                ORDER BY desired_date;  
                                                )"));
    pstmt->setString(1, date);
    pstmt->setString(2, endDate);

    std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
    while(res->next()){
        nlohmann::json tmp;
        
        tmp["date"] = res->getString("desired_date");
        tmp["count"] = res->getInt("product_count");

        answerJson.push_back(tmp);
    }
    std::cout << answerJson.dump(4) << std::endl;
    return answerJson;


 
}
nlohmann::json CarpetsGetters::extractCarpets(std::shared_ptr<sql::ResultSet> res){
    nlohmann::json answerJson = nlohmann::json::array();

    while(res->next()) {
        nlohmann::json tmp;

        tmp["address"] = res->getString("address");
        tmp["phoneNumber"] = res->getString("phone_number");
        tmp["pickupDate"] = res->getString("pickup_date");
        tmp["desiredDate"] = res->getString("desired_date");  
        tmp["status"] = res->getString("status");
        tmp["code"] = res->getString("code"); 
        
        answerJson.push_back(tmp); 
        
    }

        std::cout << answerJson.dump(4) << std::endl;
    return answerJson;
}
nlohmann::json CarpetsGetters::getCarpetForDeliveriConcretWorker(int workerId){
    std::cout << "Worker id = " << workerId << std::endl;
    std::unique_ptr<sql::PreparedStatement> pstmp(connection->prepareStatement(R"(
        Select address, entrance, floor, flat, phone_number, delivery_time_min, delivery_time_max, price, surface   From Carpets
        Where id_delivery_to_home = ? and status = 'inDelivery'
    )"));
    pstmp->setInt(1, workerId);

    std::unique_ptr<sql::ResultSet> res(pstmp->executeQuery());

    std::map<std::string, DeliveryAddresContent> addressCarts;
    
    while(res->next()){
        std::string address = res->getString("address"); 
        std::string entrance = res->getString("entrance"); 
        std::string floor = res->getString("floor"); 
        std::string flat = res->getString("flat"); 
        std::string phone_number = res->getString("phone_number"); 
        std::string delivery_time_min = res->getString("delivery_time_min"); 
        std::string delivery_time_max = res->getString("delivery_time_max"); 
        double price = res->getDouble("price");
        double surface = res->getDouble("surface");
        
        std::string kay = address + entrance + floor + flat;
        DeliveryAddresContent& actualAddresCard = addressCarts[kay];

        if(actualAddresCard.phone_number != phone_number){
            actualAddresCard.address           = address;
            actualAddresCard.entrance          = entrance;
            actualAddresCard.floor             = floor;
            actualAddresCard.flat              = flat;
            actualAddresCard.phone_number      = phone_number;
            actualAddresCard.delivery_time_min = delivery_time_min;
            actualAddresCard.delivery_time_max = delivery_time_max;
            actualAddresCard.totalPrice        = price;
            actualAddresCard.totalSurface      = surface;
            actualAddresCard.carpetsCount      = 1;
        }else{
            actualAddresCard.totalPrice += price;
            actualAddresCard.totalSurface += surface;
            actualAddresCard.carpetsCount ++;
        }
    }
    nlohmann::json answerJson = nlohmann::json::array();
    for(auto it = addressCarts.begin();  it != addressCarts.end(); ++it){
        std::cout << "ok" << std::endl;
        std::cout << it->second.phone_number << std::endl;
        answerJson.push_back(it->second.to_json());
    }
    return answerJson;
}
<<<<<<< HEAD
nlohmann::json CarpetsGetters::getWashedCarpetsWithDay(std::string day){
    nlohmann::json answerJson;
    nlohmann::json date = nlohmann::json::array();
=======
nlohmann::json CarpetsGetters::getTodaysWashedCarpets(){
    nlohmann::json answerJson;
    nlohmann::json date = nlohmann::json::array();
    std::string todayDate = time->getTodaysDate();
>>>>>>> f454e2f15b0011818af90f5d6e6a46eda2bd2d10
    std::unique_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement(R"(Select surface, price, code 
                                                                      From Carpets
                                                                      where wash_date=?)"));

<<<<<<< HEAD
    pstmt->setString(1, day);
=======
    pstmt->setString(1, todayDate);
>>>>>>> f454e2f15b0011818af90f5d6e6a46eda2bd2d10

    std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
    int totalCount = 0;
    double totalSurface = 0;
    double totalPrice = 0;
    while(res->next()){
        nlohmann::json tmp;
        
        double surface = res->getDouble("surface");
        double price = res->getDouble("price");
      
       
        tmp["surface"] = surface;
        tmp["price"]   = price;
        tmp["code"]    = res->getString("code");
        
        totalCount++;
        totalPrice += price;
        totalSurface += surface;
       
        date.push_back(tmp);
    }
    answerJson["totalSurface"] = totalSurface;
    answerJson["totalCount"] = totalCount;
    answerJson["totalPrice"] = totalPrice;
    answerJson["date"] = date;
    std::cout << answerJson.dump(4) << std::endl;
    return answerJson;

}
double CarpetsGetters::getCarpetPrice(std::string code){
    double price = 0;
    std::unique_ptr<sql::PreparedStatement> pstmp(connection->prepareStatement(R"(
        Select price From Carpets
        Where code = ?
    )"));
    pstmp->setString(1, code);

    std::unique_ptr<sql::ResultSet> res(pstmp->executeQuery());
    if(res->next()){    
        price = res->getDouble("price");
    }

    return price;
}
nlohmann::json CarpetsGetters::getInDeliveredCarpetsFullInfoFromAddress(nlohmann::json& json){
    std::string address = json["address"];
    std::string phoneNUmber = json["phoneNumber"];
    nlohmann::json answerJson = nlohmann::json::array();
    std::unique_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement(R"(
        SELECT price, code, surface From Carpets 
        WHERE address = ? and phone_number = ? and status='inDelivery'
    )"));

    pstmt->setString(1, address);
    pstmt->setString(2, phoneNUmber);

    std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

    while(res->next()){
        nlohmann::json tmp;
        
        tmp["code"] = res->getString("code");
        tmp["price"] = res->getDouble("price");
        tmp["surface"] = res->getString("surface");

        answerJson.push_back(tmp);
    }

    return answerJson;
}
