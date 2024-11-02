#include "../../evantSwitch.hpp"
#include "../../dataBase.hpp"
#include <boost/beast/http/status.hpp>
#include <nlohmann/json_fwd.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio.hpp>
#include <boost/beast/http/verb.hpp>
using request = boost::beast::http::request<boost::beast::http::string_body>;
using response = boost::beast::http::response<boost::beast::http::string_body>;

void getIntervalWashedCarpets(const request& req, response& res , DataBase& db);
void getIntervalDeliveredCarpets(const request& req, response& res , DataBase& db);
void getConcretDayWashedCarpets(const request& req, response& res , DataBase& db);


void evantSwitchInitalaizCarpetsManipulationGettersForAdmin(EvantSwitch& evantsMap);