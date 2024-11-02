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


void getCarpets(const request& req, response& res , DataBase& db);
void getWashedCarpets(const request& req, response& res , DataBase& db);

void getTodayDelivereredCarpets(const request& req, response& res , DataBase& db);

void prepareCarpetForDelivery(const request& req, response& res , DataBase& db);
void getActualCarpetForWasher(const request& req, response& res , DataBase& db);
void getCarpetInfo(const request& req, response& res , DataBase& db);
void getCarpetsForWash(const request& req, response& res , DataBase& db);
void getCarpetForDeliveriConcretWorker(const request& req, response& res , DataBase& db);
void getInDeliveredCarpetsFullInfoFromAddress(const request& req, response& res , DataBase& db);
void getTodayWashedCarpets(const request& req, response& res , DataBase& db);
void getHeavyBurden(const request& req, response& res , DataBase& db);









void evantSwitchInitalaizCarpetsManipulationGetters(EvantSwitch& evantsMap);
