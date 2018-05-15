#ifndef CGSPINBOXEVENT_H
#define CGSPINBOXEVENT_H

#include "../CgBase/CgBaseEvent.h"
#include "glm/glm.hpp"
#include <iostream>


class CgSpinboxEvent:public CgBaseEvent
{
private:
        Cg::EventType c_type;
        float value;

public:
       CgSpinboxEvent(Cg::EventType type, float value);
       ~CgSpinboxEvent();
       Cg::EventType  getType();
       CgBaseEvent* clone();
       int getValue();
};

#endif // CGSPINBOXEVENT_H
