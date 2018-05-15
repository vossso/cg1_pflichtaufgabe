#ifndef CGCONE_H
#define CGCONE_H

#define _USE_MATH_DEFINES
#define RADIUS 0.25
#include <vector>
#include <glm/glm.hpp>
#include <math.h>
#include "CgBase/CgBaseTriangleMesh.h"

#include "CgMyPolyline.h"

class CgCone: public CgBaseTriangleMesh
{
public:
    CgCone(unsigned int id);
    ~CgCone();

    const std::vector<glm::vec3>& getVertices() const;
    const std::vector<glm::vec3>& getVertexNormals() const;
    const std::vector<glm::vec3>& getVertexColors() const;
    const std::vector<glm::vec2>& getVertexTexCoords() const;

    const std::vector<unsigned int>& getTriangleIndices() const;

    const std::vector<glm::vec3>& getFaceNormals() const;
    const std::vector<glm::vec3>& getFaceColors() const;

    Cg::ObjectType getType() const;
    unsigned int getID() const;

    void createBase(glm::vec3, bool, float);
    void createSurface(float);
    glm::vec3 calcCross(glm::vec3 zero, glm::vec3 one, glm::vec3 two);

    glm::vec3 calcPinpoint(glm::vec3 zero, glm::vec3 one, glm::vec3 two);
    std::vector<CgMyPolyline*> getNormals();
    void calcNormals();
    void setLayers(float);
    void setCurrentRes(float);
    void setResolution(float, float);
    void connectTop();

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

};

inline Cg::ObjectType  CgCone::getType() const {return m_type;}
inline unsigned int CgCone::getID() const {return m_id;}


#endif // CGCONE_H
