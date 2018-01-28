#ifndef __COLOR_HPP__
#define __COLOR_HPP__

#include <SFML/Graphics/Color.hpp>

#include <vector>

namespace plb {
    class Color : public sf::Color {
    public:
        static const unsigned MAX_RAND_COLOR = 8; // MAX_BOT
        static const sf::Color Grey;
        static sf::Color selectRandomSingle();
    private:
        static std::vector<sf::Color> colorAlreadyPicked;
        static bool contain(sf::Color c);
    };
}

#endif /* __COLOR_HPP__ */
