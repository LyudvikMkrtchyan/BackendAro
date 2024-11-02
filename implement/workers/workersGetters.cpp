#include "../../includes/workers/workersGetters.hpp"
#include <cppconn/connection.h>
#include <memory>
#include <string>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

WorkersGetters::WorkersGetters(sql::Connection* conn):connection(conn){}

std::string WorkersGetters::getWorkerNameById(int workerId){
    std::string workerName;
    std::unique_ptr<sql::PreparedStatement> pstmp(connection->prepareStatement(R"(
        SELECT name From Workers Where id = '?';
    )"));

    pstmp->setInt(1, workerId);

    std::unique_ptr<sql::ResultSet> res(pstmp->executeQuery());

    if(res->next()){
        workerName = res->getString("name");
    }

    return workerName;
    
}
