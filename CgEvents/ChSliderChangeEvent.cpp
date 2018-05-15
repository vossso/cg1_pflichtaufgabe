#include "CgSliderChangeEvent.h"


CgSliderChangeEvent::CgSliderChangeEvent(Cg::EventType type, Cg::SliderEvent slider, int v){
    c_type = type;
    c_slider = slider;
    color = v;
}

CgSliderChangeEvent::~CgSliderChangeEvent(){

}


Cg::EventType CgSliderChangeEvent::getType(){
       return c_type;
}


CgBaseEvent* CgSliderChangeEvent::clone(){
    return new CgSliderChangeEvent(c_type, c_slider, color);
}

std::ostream& operator <<(std::ostream& os, const CgSliderChangeEvent& e){
    os << "Eventtype: " << e.c_type << "Value: " << e.c_slider << "Test "<< e.color << std::endl;
    return os;
}

int CgSliderChangeEvent::getColor(){
    return color;
}

Cg::SliderEvent CgSliderChangeEvent::getSlider(){
    return c_slider;
}
