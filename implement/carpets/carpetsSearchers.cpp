#include "../../includes/carpets/carpetsSearchers.hpp"
#include <cppconn/resultset.h>
#include <memory>
CarpetsSearchers::CarpetsSearchers(sql::Connection* conn):connection(conn){}
nlohmann::json CarpetsSearchers::searchCarpetsWithStatus(std::string status){
    std::unique_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement(R"(
    Select  desired_date, address, entrance, floor, flat, surface , price, code 
    From carpets Where status = ?)"));

    pstmt->setString(1, status);

    std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

    nlohmann::json answerJson = nlohmann::json::array();

    while(res->next()){
        nlohmann::json tmp;

        tmp["address"] = res->getString("address");
        tmp["entrance"] = res->getString("entrance");
        tmp["floor"] = res->getString("floor");
        tmp["flat"] = res->getString("flat");
        tmp["surface"] = res->getDouble("surface");
        tmp["price"] = res->getDouble("price");
        tmp["code"] = res->getString("code");
        tmp["desired_date"] = res->getString("desired_date");

        answerJson.push_back(tmp);

    }

    return answerJson;
}


nlohmann::json CarpetsSearchers::searchCarpetsWithPhoneNumber(std::string phoneNumber) {
    
    std::unique_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement(R"(
    Select address, phone_number, pickup_date, desired_date, , status, code 
    From carpets Where phone_number=?)"));
    pstmt->setString(1, phoneNumber);

    
    std::shared_ptr<sql::ResultSet> res(pstmt->executeQuery());
    //return extractCarpets(res);
}
nlohmann::json CarpetsSearchers::searchCarpetsWithAddress(std::string address) {
    
    std::unique_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement(R"(
    Select address, phone_number, pickup_date, expected_date, surface, price, status, code 
    From carpets Where address=?)"));
    pstmt->setString(1, address);

    
  
    std::shared_ptr<sql::ResultSet> res(pstmt->executeQuery());
   // return extractCarpets(res);
}
nlohmann::json CarpetsSearchers::searchCarpetsWithCode(std::string code) {
    
     std::unique_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement(R"(
    Select address, phone_number, pickup_date, expected_date, surface, price, status, code 
    From carpets Where code=?)"));
    pstmt->setString(1, code);

    
    std::shared_ptr<sql::ResultSet> res(pstmt->executeQuery());
   // return extractCarpets(res);
}