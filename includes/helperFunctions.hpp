#include "evantSwitch.hpp"
#include <boost/beast/http/status.hpp>
#include <nlohmann/json_fwd.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio.hpp>
#include <boost/beast/http/verb.hpp>

#include "./evants/carpetsManipulation/carpetsManipulationSetters.hpp"
#include "./evants/carpetsManipulation/carpetsManipulationGetters.hpp"

#include "./evants/carpetsManipulation/carpetsManipulationGettersForAdmin.hpp"



void evantSwitchInitalaiz(EvantSwitch& evantsMap);