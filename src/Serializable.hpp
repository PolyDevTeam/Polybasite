#ifndef __SERIALIZABLE_HPP__
#define __SERIALIZABLE_HPP__

#include <string>

class Serializable {
public:
    Serializable();
    virtual ~Serializable();
    virtual std::string serialize();
    virtual void deserialize(std::string &serializable);
};

#endif /* __SERIALIZABLE_HPP__ */
