#include <iostream>
#include <src/ioc.h>
#include "src/icommand.h"
#include "src/object.h"
#include "src/producer.h"
#include "src/safequeue.h"

int main(int ac, char **av)
{
    std::cout << std::endl;
    std::cout << "Testing thread methods..." << std::endl;
    producer a1;
    a1.test_thread1();
    //test_thread2();
    return 0;
}
