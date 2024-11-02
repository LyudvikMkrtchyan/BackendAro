#include "../includes/salaries.hpp"
#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <memory>

Finances::Finances(sql::Connection* conn):connection(conn){}

void Finances::setTransactionWashFinance(int washerId, int amount,std::string code){
    std::string todayDate = time->getTodaysDate();

    std::unique_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement(R"(Insert into Salaries
                                                                (worker_id, amount, transaction_type, transaction_date, description)
                                                                Values(?,?,'income', ?, ?))"));
    pstmt->setInt(1, washerId);
    pstmt->setInt(2, amount);
    pstmt->setDateTime(3, todayDate);
    pstmt->setString(4, code);

    pstmt->execute();

}

void Finances::addTodaysRecivetSealory(nlohmann::json& json){
    for(int  i = 0; i < json.size(); ++i){
        std::string todayDate = time->getTodaysDate();
        std::unique_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement(R"(SELECT 1 FROM Salaries 
                                                                                            WHERE worker_id = ? and transaction_date=? 
                                                                                            LIMIT 1;)"));
        pstmt->setInt(1, json[i]["id"]);
        pstmt->setString(2, todayDate);

        std::unique_ptr<sql::ResultSet> res( pstmt->executeQuery());
        if(res->next()){
            json[i]["status"] = "Paid";
        }else{
            json[i]["status"] = "Unpaid";

        }
    }
}

void Finances::setWorkerSealory(int workerId, int amount){
    std::cout << "ok" << std::endl;
    std::unique_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement(R"(Insert Into Finances
                                                                                        (worker_id, amount, transaction_type, transaction_date)
                                                                                        Values(?,?,'income', ?))"));
    std::cout << "ok" << std::endl;
    
    std::string todayDate = time->getTodaysDate();

    pstmt->setInt(1, workerId);
    pstmt->setInt(2, amount);
    pstmt->setString(3, todayDate);

    pstmt->execute();
}

void Finances::carpetIsDeliveredFinances(std::string code, double price){
    std::string todayDate = time->getTodaysDate();
    std::string category = "delivery";
    std::unique_ptr<sql::PreparedStatement> pstmp(connection->prepareStatement(R"(
    Insert INTO Finance_records
    (record_date, category, description, income)
    Values(? , ? , ? , ?) 
    )"));
    pstmp->setString(1, todayDate);
    pstmp->setString(2, category);
    pstmp->setString(3, code);
    pstmp->setDouble(4, price);
    pstmp->execute();
}