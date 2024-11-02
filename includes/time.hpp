#pragma once
#include <string>
#include <ctime> 
#include <iostream> 
#include <sstream> 
#include <iomanip> 
#include <ctime>      
#include <mysql/mysql.h> 
class Time{
public:
  MYSQL_TIME convertToMySQLTime(const std::string& timeStr);
  std::string getTodaysDate();
  std::string addDaysToDate(std::string dateStr, int daysToAdd);
};