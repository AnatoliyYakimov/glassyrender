

#ifndef GLASSYRENDER_SINGLETON_H
#define GLASSYRENDER_SINGLETON_H

class singleton {
public:
    singleton(const singleton &s) = delete;
    singleton &operator=(const singleton &s) = delete;

protected:
    singleton() = default;
    virtual ~singleton() = default;
};

#endif //GLASSYRENDER_SINGLETON_H
