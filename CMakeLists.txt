cmake_minimum_required(VERSION 3.10)

project(MyProject)

set(SOURCES
    ./implement/evants/carpetsManipulation/carpetsManipulation.cpp
    ./implement/evants/carpetsManipulation/carpetsManipulationGetters.cpp
    ./implement/evants/carpetsManipulation/carpetsManipulationSetters.cpp
    ./implement/evants/carpetsManipulation/carpetsManipulationGettersForAdmin.cpp
    ./implement/evants/financeEvants/financeGettersEvants.cpp
    
    
    ./implement/evants/workerEvants.cpp
    ./implement/evants/ordersEvants.cpp
    ./implement/evants/optionsEvants.cpp
    ./implement/evants/complexOperationEvants.cpp
    
    ./implement/dataBase.cpp
    ./implement/orders.cpp
    ./implement/evantSwitch.cpp
    ./implement/helperFunctions.cpp
    ./implement/main.cpp
    ./implement/network.cpp
    
    ./implement/carpets/carpets.cpp
    ./implement/carpets/carpetsGetters.cpp
    ./implement/carpets/carpetsSetters.cpp
    ./implement/carpets/carpetsSearchers.cpp

    ./implement/carpets/carpetsGettersForAdmin.cpp
    ./implement/workers/workers.cpp
    ./implement/workers/workersGetters.cpp
    
    
    ./implement/salaries.cpp
    
    ./implement/salaries.cpp
    ./implement/options.cpp
    ./implement/time.cpp
)

add_executable(MyExecutable ${SOURCES})

target_link_libraries(MyExecutable mysqlcppconn)
