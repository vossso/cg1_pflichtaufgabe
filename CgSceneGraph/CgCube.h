#ifndef CGCUBE_H
#define CGCUBE_H

#include <vector>
#include <glm/glm.hpp>

#include "CgBase/CgBaseTriangleMesh.h"
#include "CgSceneGraph/CgMyPolyline.h"

class CgCube : public CgBaseTriangleMesh
{

public:
    CgCube();
    CgCube(int id);
    ~CgCube();

    //inherited from CgBaseRenderableObject
    Cg::ObjectType getType() const;
    unsigned int getID() const;

    //inherited from CgBaseTriangleMesh
    const std::vector<glm::vec3>& getVertices() const;
    const std::vector<glm::vec3>& getVertexNormals() const;
    const std::vector<glm::vec3>& getVertexColors() const;
    const std::vector<glm::vec2>& getVertexTexCoords() const;

    const std::vector<unsigned int>& getTriangleIndices() const;

    const std::vector<glm::vec3>& getFaceNormals() const;
    const std::vector<glm::vec3>& getFaceColors() const;
    glm::vec3 calcCross(glm::vec3 zero, glm::vec3 one, glm::vec3 two);

    glm::vec3 calcPinpoint(glm::vec3 zero, glm::vec3 one, glm::vec3 two);
    std::vector<CgMyPolyline*> getNormals();
    void calcNormals();


private:

    std::vector<glm::vec3> m_vertices;

    std::vector<glm::vec3> m_vertex_normals; //nicht genutzt
    std::vector<glm::vec3> m_vertex_colors; //nicht genutzt
    std::vector<glm::vec2> m_tex_coords;    //nicht genutzt
    std::vector<CgMyPolyline*> m_normals;

    std::vector<unsigned int>  m_triangle_indices;

    std::vector<glm::vec3> m_face_normals;
    std::vector<glm::vec3> m_face_colors;

    const Cg::ObjectType m_type;
    const unsigned int m_id;
    CgIdCounter* m_counter;




};



inline Cg::ObjectType  CgCube::getType() const {return m_type;}
inline unsigned int CgCube::getID() const {return m_id;}

#endif // CGCUBE_H
