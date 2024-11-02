#pragma once
#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>


class WorkersGetters{
public:
    WorkersGetters(sql::Connection* conn);
    std::string getWorkerNameById(int workerId);
private:
    sql::Connection* connection;
};