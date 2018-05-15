#ifndef CGMYPOLYLINE_H
#define CGMYPOLYLINE_H

#include "CgBase/CgBasePolyline.h"
#include "CgSceneGraph/CgIdCounter.h"

class CgMyPolyline : public CgBasePolyline
{

private:

    unsigned int lineWidth;
    glm::vec3 color;
    std::vector<glm::vec3> vertices;
    const Cg::ObjectType m_type;
    const unsigned int m_id;
    CgIdCounter* m_counter;

public:
    ~CgMyPolyline();

    Cg::ObjectType getType() const;
    unsigned int getID() const;
    CgMyPolyline(glm::vec3 start, glm::vec3 end);
    const std::vector<glm::vec3>& getVertices()  const;
    glm::vec3               getColor()     const;
    unsigned int            getLineWidth() const;
    void setColorRed(float value);
    void setColorGreen(float value);
    void setColorBlue(float value);
};

inline Cg::ObjectType  CgMyPolyline::getType() const {return m_type;}
inline unsigned int CgMyPolyline::getID() const {return m_id;}


#endif // CGPOLYLINE_H
