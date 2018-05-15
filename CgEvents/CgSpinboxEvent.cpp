#include "CgSpinboxEvent.h"

CgSpinboxEvent::CgSpinboxEvent(Cg::EventType type, float value){
    c_type = type;
    this->value = value;
}

CgSpinboxEvent::~CgSpinboxEvent(){

}

Cg::EventType  CgSpinboxEvent::getType(){
    return c_type;
}

CgBaseEvent* CgSpinboxEvent::clone(){
    return new CgSpinboxEvent(c_type, value);
}

int CgSpinboxEvent::getValue(){
    return value;
}
