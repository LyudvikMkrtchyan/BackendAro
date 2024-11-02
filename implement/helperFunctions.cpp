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
<<<<<<< HEAD
    evantSwitchInitalaizCarpetsManipulationGettersForAdmin(evantsMap);
=======
>>>>>>> f454e2f15b0011818af90f5d6e6a46eda2bd2d10
    evantSwitchInitalaizCarpetsManipulationSetters(evantsMap);
    
    
    
    evantSwitchInitalaizWorkers(evantsMap);
    evantSwitchInitalaizProductManipulation(evantsMap);
    evantSwitchInitalaizOrders(evantsMap);
    evantSwitchInitalaizOptions(evantsMap);
    evantSwitchInitalaizComplexOperations(evantsMap);
}