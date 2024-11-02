#include "../includes/helperFunctions.hpp"
#include "../includes/evants/workerEvants.hpp"
#include "../includes/evants/carpetsManipulation/carpetsManipulation.hpp"
#include "../includes/evants/ordersEvants.hpp"
#include "../includes/evants/complexOperationEvants.hpp"
#include "../includes/evants/optionsEvants.hpp"

#include <nlohmann/json_fwd.hpp>
#include <sys/types.h>



void evantSwitchInitalaiz(EvantSwitch &evantsMap){
    evantSwitchInitalaizCarpetsManipulationGetters(evantsMap);

    evantSwitchInitalaizCarpetsManipulationGettersForAdmin(evantsMap);
    evantSwitchInitalaizCarpetsManipulationSetters(evantsMap);
    
    
    
    evantSwitchInitalaizWorkers(evantsMap);
    evantSwitchInitalaizProductManipulation(evantsMap);
    evantSwitchInitalaizOrders(evantsMap);
    evantSwitchInitalaizOptions(evantsMap);
    evantSwitchInitalaizComplexOperations(evantsMap);
}