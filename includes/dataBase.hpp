#pragma once
#include "./carpets/carpets.hpp"
<<<<<<< HEAD
#include "./workers/workers.hpp"
#include "time.h"
=======
#include "time.h"
#include "workers.hpp"
>>>>>>> f454e2f15b0011818af90f5d6e6a46eda2bd2d10
#include "options.hpp"
#include "salaries.hpp"
#include "orders.hpp"
#include <cppconn/connection.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <ctime>
class DataBase:public Workers, public Carpets,public Orders, public Options, public Finances{
public:
    DataBase(sql::Connection* );
private:
    sql::Connection* connection;
public:
};
sql::Connection* connect(std::string, std::string, std::string);