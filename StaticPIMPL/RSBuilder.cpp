#include <new>
#include <assert.h>

#include "RSBuilder.hpp"
#include "InternalBuilder.hpp"


class FixedMotionImplAllocator
{
    FixedMotionImplAllocator()
    {
        for (size_t i = 0; i < MAX_STRUCTS; ++i) {
            _ptrs[i] = &_store[i];
            _taken[i] = false;
        }
    }


    static FixedMotionImplAllocator& Instance()
    {
        return _instance;
    }

    void *Allocate()
    {
        for (size_t i = 0; i < MAX_STRUCTS; ++i) {
            if (!_taken[i]) {
                _taken[i] = true;
                return _ptrs[i];
            }
        }
        return nullptr;
    }

    void Deallocate(void *in)
    {
        for (size_t i = 0; i < MAX_STRUCTS; ++i) {
            if (_ptrs[i] == in) {
                _taken[i] = false;
                return;
            }
        }
        assert(false, "Passed a pointer which we didnt give out.");
    }
    
private:

    static const size_t MAX_STRUCTS = 50;

    static InternalBuilder _store[MAX_STRUCTS];
    static void* _ptrs[MAX_STRUCTS];
    static bool _taken[MAX_STRUCTS];
    
    static FixedMotionImplAllocator _instance;

};


struct MotionImpl
{

    void * operator new(size_t size)
    {

    }

    void operator delete(void *)
    {

    }


    InternalBuilder *impl;

};


RSMotion::RSMotion() :
    ptr(new (_typeMem) InternalBuilder)
{
    
}

RSMotion::~RSMotion()
{
    ptr->~InternalBuilder();
}

void RSMotion::setRobot(int robotId)
{
    ptr->robotId = robotId;
}

int RSMotion::getRobot()
{
    return ptr->robotId;
}


