#include "../../includes/carpets/carpets.hpp"
#include <cppconn/connection.h>
#include <cppconn/datatype.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include <memory>
#include <nlohmann/detail/conversions/to_chars.hpp>
#include <nlohmann/json_fwd.hpp>


Carpets::Carpets(sql::Connection* conn):CarpetsSetters(conn)
                                        ,CarpetsGetters(conn)
                                        ,CarpetsSearchers(conn)

                                        ,CarpetsGettersForAdmin(conn)
                                        ,connection(conn){}











void Carpets::changeCarpetInfo(nlohmann::json& json){
    std::unique_ptr<sql::PreparedStatement> pstmp(connection->prepareStatement(R"(UPDATE Carpets
                                                                                        SET address = ?, flat = ?, floor = ?, entrance = ?, phone_number = ?
                                                                                        WHERE code = ?)"));
    std::string address     = json["address"];
    std::string flat        = json["flat"];
    std::string floor       = json["floor"];
    std::string entrance    = json["entrance"];
    std::string phoneNumber = json["phoneNumber"];
    std::string code        = json["code"];

    pstmp->setString(1, address);
    pstmp->setString(2, flat);
    pstmp->setString(3, floor);
    pstmp->setString(4, entrance);
    pstmp->setString(5, phoneNumber);
    pstmp->setString(6, code);

    pstmp->execute();
  
    
}
 
