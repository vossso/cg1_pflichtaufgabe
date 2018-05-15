#ifndef CGCHECKBOXEVENT_H
#define CGCHECKBOXEVENT_H



#include "../CgBase/CgBaseEvent.h"
#include "glm/glm.hpp"
#include <iostream>


class CgCheckBoxEvent:public CgBaseEvent
{
private:
        Cg::EventType c_type;


public:
       CgCheckBoxEvent(Cg::EventType);
       ~CgCheckBoxEvent();
       Cg::EventType  getType();
       CgBaseEvent* clone();


};

#endif // CGCHECKBOXEVENT_H
