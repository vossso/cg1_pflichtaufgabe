#ifndef CGCOLORCHANGEEVENT_H
#define CGCOLORCHANGEEVENT_H

#include "../CgBase/CgBaseEvent.h"
#include "glm/glm.hpp"
#include <iostream>

class CgSliderChangeEvent: public CgBaseEvent{

private:
        Cg::SliderEvent c_slider;
        Cg::EventType c_type;
        int color;

public:
       CgSliderChangeEvent(Cg::EventType type, Cg::SliderEvent slider, int v);
       ~CgSliderChangeEvent();
       Cg::EventType  getType();
       CgBaseEvent* clone();
       int getColor();
       Cg::SliderEvent getSlider();



       friend std::ostream& operator <<(std::ostream& os, const CgSliderChangeEvent& e);

};

#endif // CGCOLORCHANGEEVENT_H
