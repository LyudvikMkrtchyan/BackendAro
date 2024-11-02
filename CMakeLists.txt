cmake_minimum_required(VERSION 3.10)

project(MyProject)

set(SOURCES
    ./implement/evants/carpetsManipulation/carpetsManipulation.cpp
    ./implement/evants/carpetsManipulation/carpetsManipulationGetters.cpp
    ./implement/evants/carpetsManipulation/carpetsManipulationSetters.cpp
<<<<<<< HEAD
    ./implement/evants/carpetsManipulation/carpetsManipulationGettersForAdmin.cpp
=======
>>>>>>> f454e2f15b0011818af90f5d6e6a46eda2bd2d10
    

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
<<<<<<< HEAD
    ./implement/carpets/carpetsGettersForAdmin.cpp
    ./implement/workers/workers.cpp
    ./implement/workers/workersGetters.cpp
    
    
    ./implement/salaries.cpp
=======
    
    ./implement/salaries.cpp
    ./implement/workers.cpp
>>>>>>> f454e2f15b0011818af90f5d6e6a46eda2bd2d10
    ./implement/options.cpp
    ./implement/time.cpp
)

add_executable(MyExecutable ${SOURCES})

target_link_libraries(MyExecutable mysqlcppconn)
