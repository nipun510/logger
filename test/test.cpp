
#include <logger.hpp>
#include <iostream>
#include <fstream>
#include <thread>

int main()
{
    
    info("Hello Word");
    
    error("Error detectred");

    std::thread t1([](){info("Running from inside the thread");});
    std::thread t2([](){info("Running from inside the thread");});
    std::thread t3([](){info("Running from inside the thread");});
    warn("Memory exhausted");
    std::thread t4([](){info("Running from inside the thread");});
    std::thread t5([](){info("Running from inside the thread");});
    std::thread t6([](){info("Running from inside the thread");});

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();



}
