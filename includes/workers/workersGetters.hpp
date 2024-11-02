#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>
#include <memory>
#include "nlohmann/json.hpp"

class WorkersGetters{
public:
    WorkersGetters(sql::Connection* conn);
    std::string getWorkerNameById(int workerId);
private:
    sql::Connection* connection;
};