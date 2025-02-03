#include <iostream>
#include "ioc.h"
#include "icommand.h"
#include "object.h"
#include "producer.h"
#include "safequeue.h"

int main(int ac, char **av)
{
    std::cout << std::endl;
    std::cout << "Testing thread methods..." << std::endl;
    producer a1;
    a1.test_thread1();
    //test_thread2();
    return 0;
}
