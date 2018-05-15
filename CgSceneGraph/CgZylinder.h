#ifndef CGZYLINDER_H
#define CGZYLINDER_H
#define _USE_MATH_DEFINES
#define RADIUS 0.25
#include <vector>
#include <glm/glm.hpp>
#include <math.h>
#include "CgBase/CgBaseTriangleMesh.h"

#include "CgMyPolyline.h"
#include "CgSceneGraph/CgIdCounter.h"

class CgZylinder: public CgBaseTriangleMesh
{
public:
    CgZylinder();
    ~CgZylinder();

    const std::vector<glm::vec3>& getVertices() const;
    const std::vector<glm::vec3>& getVertexNormals() const;
    const std::vector<glm::vec3>& getVertexColors() const;
    const std::vector<glm::vec2>& getVertexTexCoords() const;

    const std::vector<unsigned int>& getTriangleIndices() const;

    const std::vector<glm::vec3>& getFaceNormals() const;
    const std::vector<glm::vec3>& getFaceColors() const;

    virtual Cg::ObjectType getType() const;
    virtual unsigned int getID() const;

    //Erzeugt Boden und Decke
    virtual void createBaseAreas(glm::vec3, bool, float);
    //Erzeugt beliebig viele Zwischenebenen und verbindet die Aussenfläche
    virtual void createSurface(float);
    virtual glm::vec3 calcCross(glm::vec3 zero, glm::vec3 one, glm::vec3 two);

    virtual glm::vec3 calcPinpoint(glm::vec3 zero, glm::vec3 one, glm::vec3 two);
    virtual std::vector<CgMyPolyline*> getNormals();
    virtual void calcNormals();


    virtual void setLayers(float);
    virtual void setLayerResolution(float);

    virtual void setResolution(float, float);
    //verbindet die Decke mit der letzten zwischenebene
    virtual void connectTop();

private:
    std::vector<glm::vec3> m_vertices;
    std::vector<glm::vec3> m_vertex_normals;
    std::vector<glm::vec3> m_vertex_colors;
    std::vector<glm::vec2> m_tex_coords;
    std::vector<unsigned int> m_triangle_indices;
    std::vector<glm::vec3> m_face_normals;
    std::vector<glm::vec3> m_face_colors;
    const Cg::ObjectType m_type;
    const unsigned int m_id;
    glm::vec3 hight;

    std::vector<glm::vec3> testvec;
    std::vector<glm::vec4> cylinder_vert;


    int size;
    std::vector<CgMyPolyline*> m_normals;
    float currentRes;
    int layers;
    CgIdCounter* m_counter;

};

inline Cg::ObjectType  CgZylinder::getType() const {return m_type;}
inline unsigned int CgZylinder::getID() const {return m_id;}

#endif // CGZYLINDER_H
