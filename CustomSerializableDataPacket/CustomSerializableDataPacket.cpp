// CustomSerializableDataPacket.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

struct RobotKey
{
    int _value;
};
typedef int RobotId;

namespace arguments {

class RobotNumberInst
{
public:
    int getRobotId() const { return _robotId; }
    void setRobotId(RobotId robotId) { _robotId = robotId; }

protected:
    void serialize() { std::cout << _robotId << " "; }
    
private:
    RobotId _robotId;
};


class RobotKeyInst
{
public:
    RobotKey getRobotKey() const { return _key; }
    void setRobotKey(int keyValue) { _key._value = keyValue;  }

protected:
    void serialize() { std::cout << _key._value << " "; }

private:
    RobotKey _key;
};

template <size_t NSigs>
class ComplexSignalsInst
{
public:
    void setSignalsConseq(int start, int increment) { 
        for (auto &sig : _signals._sigs) {
            sig = start;
            start += increment;
        }
    }

    void resetSigs()
    {
        std::memset(_signals._sigs, 0, sizeof(_Signals._sigs));
    }

    void otherFunctions(int val)
    {
        //...
    }

protected:

    
    void serialize() { 
        std::cout << NSigs << " |";
        for (auto sig : _signals._sigs) {
            std::cout << sig << " ";
        }
    }

private:

    struct Signals
    {
        int _sigs[NSigs];
    };
    Signals _signals;
};



struct expand_type
{
    template <typename... T>
    expand_type(T&&...) { }
};

template <class ...Args>
class Arguments : public Args...
{
public:

    void serialize()
    {
        expand_type{ 0, (this->Args::serialize(), 0)... };
    }
};

typedef Arguments<RobotNumberInst, RobotKeyInst> KeyArguments;

typedef Arguments<RobotNumberInst, ComplexSignalsInst<50>> SignalArguments;

}

int main()
{
    arguments::KeyArguments keyArgs;
    keyArgs.setRobotId(3);
    keyArgs.setRobotKey(4);

    keyArgs.serialize();


    arguments::SignalArguments sigArgs;
    sigArgs.setRobotId(5);
    sigArgs.setSignalsConseq(3, 6);

    sigArgs.serialize();


    while (true);
    return 0;
}

