#include "CgCheckBoxEvent.h"

CgCheckBoxEvent::CgCheckBoxEvent(Cg::EventType type)
{
    c_type = type;

}


CgCheckBoxEvent::~CgCheckBoxEvent(){

}

Cg::EventType  CgCheckBoxEvent::getType(){
    return c_type;
}

CgBaseEvent* CgCheckBoxEvent::clone(){
    return new CgCheckBoxEvent(c_type);
}

