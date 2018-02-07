#ifndef __PLB_HPP__
#define __PLB_HPP__

#include <string>
#include <vector>
#include <sstream>

namespace plb {
    static unsigned ownerId;

    class Util {
    public:
        static std::string extract(std::string &str, const char delimiter) {
            std::string result = str.substr(0, str.find(delimiter, 0));
            str = str.substr(str.find(delimiter, 0) + 1, str.length());
            return result;
        }
    };

    class Entity {
    public:
        Entity() : m_x(0), m_y(0) {}
        Entity(unsigned x, unsigned y) :m_x(x), m_y(y) {}
        virtual ~Entity() {}

        unsigned getX() const {
            return m_x;
        }

        unsigned getY() const {
            return m_y;
        }

        virtual void deserialize(std::string &serializable) {
            std::string result = Util::extract(serializable, ':');

            if(result != "Entity") {
                std::cerr << "Impossible to decode entity object" << std::endl;
                exit(-1);
            }

            result = Util::extract(serializable, ';');
            m_x = atoi(result.c_str());

            result = Util::extract(serializable, ';');
            m_y = atoi(result.c_str());
        }
    protected:
        unsigned m_x;
        unsigned m_y;
    };

    class BlackHole : public Entity {
    public:
        BlackHole() : Entity() {}
        BlackHole(unsigned x, unsigned y) : Entity(x, y) {}
        virtual ~BlackHole() {}

        virtual void deserialize(std::string &serializable) {
            std::string result = Util::extract(serializable, ':');

            if(result != "BlackHole") {
                std::cerr << "Impossible to decode black hole object" << std::endl;
                exit(-1);
            }

            result = Util::extract(serializable, ';');
            m_x = atoi(result.c_str());

            result = Util::extract(serializable, ';');
            m_y = atoi(result.c_str());
        }
    };

    class Basite : public Entity {
    public:
        Basite() : Entity() {}
        Basite(unsigned x, unsigned y, unsigned power) : Entity(x, y), m_power(power) {}
        virtual ~Basite() {}

        virtual void deserialize(std::string &serializable) {
            std::string result = Util::extract(serializable, ':');

            if(result != "Basite") {
                std::cerr << "Impossible to decode basite object" << std::endl;
                exit(-1);
            }

            result = Util::extract(serializable, ';');
            m_x = atoi(result.c_str());

            result = Util::extract(serializable, ';');
            m_y = atoi(result.c_str());
        }
    private:
        unsigned m_power;
    };

    class Miner : public Entity {
    public:
        Miner() : Entity() {}
        Miner(unsigned x, unsigned y) : Entity(x, y) {}
        virtual ~Miner() {}

        unsigned getOwner() const {
            return m_owner;
        }

        void deserialize(std::string &serializable) {
            std::string result = Util::extract(serializable, ':');

            if(result != "Miner") {
                std::cerr << "Impossible to decode miner object" << std::endl;
                exit(-1);
            }

            result = Util::extract(serializable, ';');
            m_x = atoi(result.c_str());

            result = Util::extract(serializable, ';');
            m_y = atoi(result.c_str());

            result = Util::extract(serializable, ';');
            m_power = atoi(result.c_str());

            result = Util::extract(serializable, ';');
            m_owner = atoi(result.c_str());
        }

        unsigned getPower() const {
            return m_power;
        }

        bool operator==(const Miner& m) {
            return m_x == m.m_x &&
                   m_y == m.m_y &&
                   m_power == m.m_power &&
                   m_owner == m.m_owner;
        }
    private:
        unsigned m_power;
        unsigned m_owner;
    };

    typedef std::vector<Entity*> VEntity;
    class Map {
    public:
        Map(unsigned width, unsigned height) : m_width(width), m_height(height) {}
        Map() : Map(0, 0){}

        virtual ~Map() {
            for (unsigned i = 0; i < m_entities.size(); ++i) {
                for (unsigned j = 0; j < m_entities[i].size(); ++j) {
                    delete m_entities[i][j];
                    m_entities[i][j] = 0;
                }
            }
        }

        void setEntity(Entity* entity);

        std::vector<Entity*>& operator[] (unsigned i) {
            return m_entities[i];
        }

        unsigned getHeight() const {
            return m_height;
        }

        unsigned getWidth() const {
            return m_width;
        }

        void deserialize(std::string &serializable) {
            std::string buff;
            m_miners.clear();

            buff = serializable.substr(0, serializable.find(":", 0));
            serializable = serializable.substr(serializable.find(":", 0)+1, serializable.length());

            if(buff != "Map") {
                std::cerr << "Impossible to decode map object" << std::endl;
                exit(-1);
            }

            buff = serializable.substr(0, serializable.find(";", 0));
            serializable = serializable.substr(serializable.find(";", 0)+1, serializable.length());
            m_width = atoi(buff.c_str());

            buff = serializable.substr(0, serializable.find(";", 0));
            serializable = serializable.substr(serializable.find(";", 0)+1, serializable.length());
            m_height = atoi(buff.c_str());

            for (unsigned i = 0; i < m_width; ++i) {
                VEntity line;

                for (unsigned j = 0; j < m_height; ++j) {
                    buff = serializable.substr(0, serializable.find(":", 0));

                    if(buff == "Entity") {
                        Entity* entity = new Entity();
                        entity->deserialize(serializable);
                        line.push_back(entity);
                    }
                    else if(buff == "BlackHole") {
                        BlackHole* blackHole = new BlackHole();
                        blackHole->deserialize(serializable);
                        line.push_back(blackHole);
                    }
                    else if(buff == "Basite") {
                        Basite* basite = new Basite();
                        basite->deserialize(serializable);
                        line.push_back(basite);
                    }
                    else if(buff == "Miner") {
                        Miner* miner = new Miner();
                        miner->deserialize(serializable);
                        line.push_back(miner);

                        if(miner->getOwner() == plb::ownerId) {
                            m_miners.push_back(miner);
                        }
                    }
                }

                m_entities.push_back(line);
            }
        }

        std::vector<Miner*> getMiners() const {
            return m_miners;
        }
    private:
        std::vector<std::vector<Entity*>> m_entities;
        std::vector<Miner*> m_miners;
        unsigned m_width;
        unsigned m_height;
    };

    enum DIRECTIONS {
        STILL = 0,
        NORTH = 1,
        EAST = 2,
        SOUTH = 3,
        WEST = 4,
    };
    class Move {
    public:
        Move(unsigned minerId, DIRECTIONS directions) : m_minerId(minerId), m_directions(directions) {

        }

        Move() : Move(0, STILL) {

        }

        virtual ~Move() {

        }

        virtual std::string serialize() {
            std::ostringstream os;

            os << "Move:" << m_minerId << ";" << m_directions << ";";

            return os.str();
        }

        bool operator<(const Move& move) const {
            return m_minerId < move.m_minerId /*&& m_directions < move.m_directions*/;
        }

        Move& operator=(const Move& move) {
            m_minerId = move.m_minerId;
            m_directions = move.m_directions;
            return *this;
        }
    private:
        unsigned m_minerId;
        DIRECTIONS m_directions;
    };
}

#endif /* __PLB_HPP__ */
