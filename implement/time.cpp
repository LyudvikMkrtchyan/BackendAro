#include "../includes/time.hpp"

std::string Time::getTodaysDate(){
    
    time_t now = time(0); 
    struct tm tstruct;
    char buffer[80];
    tstruct = *localtime(&now); 
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", &tstruct);
    std::string todayDate(buffer);
    return todayDate;
}

 std::string Time::addDaysToDate(std::string dateStr, int daysToAdd){
 std::istringstream ss(dateStr);
    std::tm date = {};


    ss >> std::get_time(&date, "%Y-%m-%d");

    if (ss.fail()) {
        std::cerr << "Ошибка чтения даты" << std::endl;
        return "";
    }

    std::time_t time = std::mktime(&date);
    

    time += daysToAdd * 24 * 60 * 60;

   
    std::tm* newDate = std::localtime(&time);
    

    std::ostringstream result;
    result << std::put_time(newDate, "%Y-%m-%d"); 
    
    return result.str();
}
MYSQL_TIME Time::convertToMySQLTime(const std::string& timeStr){
    MYSQL_TIME mysqlTime;
    int hour, minute;

    std::istringstream ss(timeStr);
    char delimiter; 

    ss >> hour >> delimiter >> minute;

    // Устанавливаем значения для MYSQL_TIME
    mysqlTime.hour = hour;
    mysqlTime.minute = minute;
    mysqlTime.second = 0;
    mysqlTime.neg = 0; 

    return mysqlTime;
}