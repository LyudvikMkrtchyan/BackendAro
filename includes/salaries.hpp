#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>
#include "nlohmann/json.hpp"
#include "time.hpp"
class Finances{
public:
    Finances(sql::Connection* conn);
    void addTodaysRecivetSealory(nlohmann::json& json);
    void setTransactionWashFinance(int washerId, int amount,std::string code);
    void setWorkerSealory(int workerId, int amount);
    void carpetIsDeliveredFinances(std::string code, double price);
private:
    sql::Connection* connection;
    Time* time;
};