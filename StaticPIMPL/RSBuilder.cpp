#include <new>

#include "RSBuilder.hpp"
#include "InternalBuilder.hpp"

static_assert(RSMotion::SIZE_OF_IMPLEMENTATION >= sizeof(InternalBuilder), "Implementation size of the Builder is smaller then it should be");



InternalBuilder *internBuilder(void *toConvert)
{
    return static_cast<InternalBuilder*>(toConvert);
}


RSMotion::RSMotion() :

    _internalMotion(new (_typeMem) InternalBuilder)
{
}

RSMotion::~RSMotion()
{
    internBuilder(_internalMotion)->~InternalBuilder();
}

void RSMotion::setRobot(int robotId)
{
    internBuilder(_internalMotion)->robotId = robotId;
}

int RSMotion::getRobot() const
{
    return internBuilder(_internalMotion)->robotId;
}


