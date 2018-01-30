#include <iostream>
#include <unistd.h>
#include <string>
#include <set>

#include "plb.hpp"
#include "networking.hpp"

int main(int argc, char* argv[]) {
    if(argc != 3)
        return -1;
    
    std::cout << "DEBUT BOT RandomBot" << std::endl;

    plb::Map map;
    initBot("RandomBot", argv, map);

    // TODO : Maybe send exit message ?
    while(1) {
        getFrame(map);

        std::set<plb::Move> moves;
        std::vector<plb::Miner*> miners = map.getMiners();

        for(unsigned i = 0; i < miners.size(); ++i) {
            plb::Move move(i, (plb::DIRECTIONS) (rand()%5));
            moves.insert(move);
        }
        
        sendFrame(moves);
    }

    std::cout << "FIN BOT" << std::endl;

    return 0;
}
