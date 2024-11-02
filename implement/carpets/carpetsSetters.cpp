#include "../../includes/carpets/carpetsSetters.hpp"
#include <cppconn/prepared_statement.h>
#include <memory>

CarpetsSetters::CarpetsSetters(sql::Connection* conn):connection(conn){}

void CarpetsSetters::addCarpet(nlohmann::json& json){
   
    std::string pickupDate = time->getTodaysDate();
    std::string address = json["address"];
    std::string entrance = json["entrance"];
    std::string phoneNumber = json["phoneNumber"];
    std::string floor = json["floor"];
    std::string flat = json["flat"];
 
    std::string code = json["code"];
    

    std::string location = json["location"];
    std::string desiredDate = json["date"];

    
    if(json.contains("idDeliveryToWash")){

    }else{
        std::unique_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement(R"(INSERT INTO Carpets 
                                                (address, entrance, phone_number, pickup_date, floor, flat, code, location, desired_date,status) 
                                                VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?,'dirty') )"));
        pstmt->setString(1, address);
        pstmt->setString(2, entrance);
        pstmt->setString(3, phoneNumber);
        pstmt->setString(4, pickupDate);
        pstmt->setString(5, floor);
        pstmt->setString(6, flat);
        pstmt->setString(7, code);
        pstmt->setString(8, location);
        pstmt->setString(9, desiredDate);


        pstmt->execute();
    }
}
void CarpetsSetters::setCarpetParametrFromWasher(nlohmann::json& json){
    std::string code = json["code"];
    int workerId = json["workerId"];
    double surface = json["surface"];
    int price = json["price"];
    price *= surface;

    std::unique_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement(R"(UPDATE Carpets
                                                                        SET washer = ?, surface = ?, price = ?, status='washing'
                                                                        WHERE code = ?;)"));
    pstmt->setInt(1, workerId);
    pstmt->setDouble(2, surface);
    pstmt->setDouble(3, price);
    pstmt->setString(4, code);

    bool ok = pstmt->execute();
}
void CarpetsSetters::setCarpetStatus(std::string carpetCode, std::string carpetStatus){
    std::unique_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement("Update Carpets Set status=? where code=?;"));

    pstmt->setString(1, carpetStatus);
    pstmt->setString(2, carpetCode);
    pstmt->execute();
}
void CarpetsSetters::setCarpetStatusDelivered(std::string code){
    std::string todayDate = time->getTodaysDate();

    std::unique_ptr<sql::PreparedStatement> pstmp(connection->prepareStatement(R"(
        UPDATE Carpets
        SET status = 'delivered' , delivery_date = ?
        WHERE code = ?
    )"));
    pstmp->setString(1, todayDate);
    pstmp->setString(2, code);

    pstmp->execute();
}
void CarpetsSetters::setCarpetStatusReadyFormDelivery(std::string carpetCode){
    std::unique_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement("Update Carpets Set status='read_for_delivery' where code=?;"));

    pstmt->setString(1, carpetCode);
    pstmt->execute();
}
void CarpetsSetters::setCarpetsParametrsForDelivery(nlohmann::json& json){
    std::unique_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement(R"(Update Carpets
                                                                                    set status='being_delivered',
                                                                                        delivery_date=?,
                                                                                        delivery_time=?
                                                                                    Where code=?)"));
    
    std::string deliveryDate = json["deliveryDate"];
    std::string deliveryTime = json["deliveryTime"];
    
    pstmt->setString(1, deliveryDate);
    pstmt->setString(2, deliveryTime);

    std::vector<std::string> codes = json["codes"].get<std::vector<std::string>>();

    for(auto code : codes){
        pstmt->setString(3, code);
        pstmt->execute();
    }
}
void CarpetsSetters::setCarpetWashDay(std::string carpetCode){
    std::unique_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement("Update Carpets Set wash_date=? where code=?;"));
    std::string dateToday = time->getTodaysDate();

    pstmt->setString(1, dateToday);
    pstmt->setString(2, carpetCode);
    pstmt->execute();
}

void CarpetsSetters::setDeliveryDataTime(nlohmann::json& json) {
    std::string desiredDate = json["desiredDate"]; 
    std::string startTime = json["startTime"]; 
    std::string endTime = json["endTime"]; 
    std::string code = json["code"];

   
    std::string fullStartTime = desiredDate + " " + startTime + ":00"; 
    std::string fullEndTime = desiredDate + " " + endTime + ":00"; 

    std::unique_ptr<sql::PreparedStatement> pstmp(connection->prepareStatement(R"(
        UPDATE Carpets
        SET desired_date = ?, delivery_time_min = ?, delivery_time_max = ?
        WHERE code = ?)"));
        
    pstmp->setString(1, desiredDate);
    pstmp->setString(2, startTime);
    pstmp->setString(3, endTime); 
    pstmp->setString(4, code); 

    pstmp->execute();
}

void CarpetsSetters::setCarpetCouirier(std::string carpetsCode, int courierId){
    std::unique_ptr<sql::PreparedStatement> pstmp(connection->prepareStatement(R"(
        UPDATE Carpets
        SET id_delivery_to_home = ?,
            status = 'inDelivery'
        WHERE code = ? ;
    )"));

    pstmp->setInt(1,  courierId);
    pstmp->setString(2,  carpetsCode);

    pstmp->execute();
}

 