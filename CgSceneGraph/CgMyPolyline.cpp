
#include "CgMyPolyline.h"


CgMyPolyline::CgMyPolyline( glm::vec3 start, glm::vec3 end):
m_type(Cg::Polyline),
m_counter(new CgIdCounter),
m_id(m_counter->getId())
{

    vertices.push_back(start);

    vertices.push_back(start += end);

    color = glm::vec3(0,0,0);
    lineWidth =5;


}

CgMyPolyline::~CgMyPolyline(){
    vertices.clear();
}

const std::vector<glm::vec3>& CgMyPolyline::getVertices()  const{
    return vertices;
}
glm::vec3 CgMyPolyline::getColor()     const{
    return color;
}
unsigned int CgMyPolyline::getLineWidth() const{
    return lineWidth;
}

void CgMyPolyline::setColorRed(float value){
    color.x = value/256;
}

void CgMyPolyline::setColorGreen(float value){
    color.y = value/256;
}

void CgMyPolyline::setColorBlue(float value){
    color.z = value/256;
}







