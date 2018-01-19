#include <iostream>
#include <unistd.h>

#include <string>

//#include "hlt.hpp"
#include "networking.hpp"

int main(int argc, char* argv[]) {
    if(argc != 3)
        return -1;

    sleep(3);

    std::cout << "HELLO WORLD" << std::endl;

    // TODO : Unserialize map function
    // TODO : Send miner movements

    initBot("RandomBot", argv);

    std::cout << "FIN BOT" << std::endl;

    return 0;
}
