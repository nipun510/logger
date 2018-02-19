
#include <logger.hpp>
#include <iostream>

int main()
{
    logger::logger l;
    l.addstream(std::cout, true);
    l.info("Hello Word");
    l.error("Error detectred");
    l.warn("Memory exhausted");

}
