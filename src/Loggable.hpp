#ifndef __LOGGABLE_HPP__
#define __LOGGABLE_HPP__

class Loggable {
public:
    virtual std::string toString() const;
    virtual ~Loggable();
};

#endif /* __LOGGABLE_HPP__ */
