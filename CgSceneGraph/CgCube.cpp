#include "CgCube.h"
#include "CgBase/CgEnums.h"
#include <iostream>

CgCube::CgCube(int id):
m_type(Cg::TriangleMesh),
m_id(id)
{
    m_vertices.push_back(glm::vec3(-0.5,0.0,0.0));
    m_vertices.push_back(glm::vec3(0.5,-0.5,0.0));
    m_vertices.push_back(glm::vec3(0.0,0.5,0.0));

    m_triangle_indices.push_back(0);
    m_triangle_indices.push_back(1);
    m_triangle_indices.push_back(2);

    m_vertex_normals.push_back(glm::vec3(0.0,0.0,1.0));
    m_vertex_normals.push_back(glm::vec3(0.0,0.0,1.0));
    m_vertex_normals.push_back(glm::vec3(0.0,0.0,1.0));

}

CgCube::CgCube():
m_type(Cg::TriangleMesh),
m_counter(new CgIdCounter),
m_id(m_counter->getId())
{
    //m_vertices beinhaltet alle Punkte des zu erzäugenden Würfels.
    m_vertices.push_back(glm::vec3(-0.25,0.25,-0.25));
    m_vertices.push_back(glm::vec3(-0.25,-0.25,-0.25));
    m_vertices.push_back(glm::vec3(0.25,0.25,-0.25));
    m_vertices.push_back(glm::vec3(0.25,-0.25,-0.25));
    m_vertices.push_back(glm::vec3(-0.25,0.25,0.25));
    m_vertices.push_back(glm::vec3(-0.25,-0.25,0.25));
    m_vertices.push_back(glm::vec3(0.25,0.25,0.25));
    m_vertices.push_back(glm::vec3(0.25,-0.25,0.25));


    //m_triangle_indices speichert Reihenfolge der zu einem Dreieck zugehörigen Punkte.
    //Seite A
    m_triangle_indices.push_back(3);
    m_triangle_indices.push_back(1);
    m_triangle_indices.push_back(2);

    m_triangle_indices.push_back(2);
    m_triangle_indices.push_back(1);
    m_triangle_indices.push_back(0);

    //Seite B
    m_triangle_indices.push_back(4);
    m_triangle_indices.push_back(6);
    m_triangle_indices.push_back(0);

    m_triangle_indices.push_back(0);
    m_triangle_indices.push_back(6);
    m_triangle_indices.push_back(2);

    //Seite C
    m_triangle_indices.push_back(5);
    m_triangle_indices.push_back(7);
    m_triangle_indices.push_back(4);

    m_triangle_indices.push_back(4);
    m_triangle_indices.push_back(7);
    m_triangle_indices.push_back(6);

    //Seite D
    m_triangle_indices.push_back(7);
    m_triangle_indices.push_back(3);
    m_triangle_indices.push_back(6);

    m_triangle_indices.push_back(6);
    m_triangle_indices.push_back(3);
    m_triangle_indices.push_back(2);

    //Seite E
    m_triangle_indices.push_back(1);
    m_triangle_indices.push_back(5);
    m_triangle_indices.push_back(0);

    m_triangle_indices.push_back(0);
    m_triangle_indices.push_back(5);
    m_triangle_indices.push_back(4);

    //Seite F
    m_triangle_indices.push_back(1);
    m_triangle_indices.push_back(3);
    m_triangle_indices.push_back(5);

    m_triangle_indices.push_back(5);
    m_triangle_indices.push_back(3);
    m_triangle_indices.push_back(7);




    calcNormals();

}



CgCube::~CgCube()
{
    m_vertices.clear();
    m_vertex_normals.clear();
    m_vertex_colors.clear();
    m_tex_coords.clear();
    m_triangle_indices.clear();
    m_face_normals.clear();
    m_face_colors.clear();
    m_normals.clear();
}

//Berechnet alle Normalen für jedes Dreieck des Würfels und speichert diese als CgMyPolyline im Vector m.normals.
void CgCube::calcNormals(){
    int j = 2;
    //Für einen Durchlauf der Schleife werden 3 Punkte benutzt
    for(unsigned int i = 0; i < m_triangle_indices.size(); i = i + 3,j++){
        m_normals.push_back(new CgMyPolyline(
                //Schwerpunkt für aktuelles Dreieck berechnen
                calcPinpoint(
                m_vertices[m_triangle_indices[i]],
                m_vertices[m_triangle_indices[i+1]],
                m_vertices[m_triangle_indices[i+2]]),
                //Normalenausrichtung für aktuelles Dreieck berechnen
                calcCross(
                m_vertices[m_triangle_indices[i]],
                m_vertices[m_triangle_indices[i+1]],
                m_vertices[m_triangle_indices[i+2]])));
    }
}


std::vector<CgMyPolyline*> CgCube::getNormals(){
    return m_normals;
}

//Berechnet den Schwerpunkt eines übergebenen Dreiecks. Übergabe des Dreiecks erfolgt durch die drei Eckpunkte.
glm::vec3 CgCube::calcPinpoint(glm::vec3 zero, glm::vec3 one, glm::vec3 two){
    glm::vec3 pinpoint;
    pinpoint = zero += one;
    pinpoint += two;
    pinpoint = glm::vec3(pinpoint.x*1/3,pinpoint.y*1/3,pinpoint.z*1/3);

    return pinpoint;

}

//Berechnet die Normalen-Ausrichtung eines übergebenen Dreiecks. Übergabe des Dreiecks erfolgt durch die drei Eckpunkte.
glm::vec3 CgCube::calcCross(glm::vec3 zero, glm::vec3 one, glm::vec3 two){
    return (glm::cross((two -= one), (zero -= one)));

}



const std::vector<glm::vec3>& CgCube::getVertices() const
{
    return m_vertices;
}

const std::vector<glm::vec3>& CgCube::getVertexNormals() const
{
    return m_vertex_normals;
}

const std::vector<glm::vec3>& CgCube::getVertexColors() const
{
     return m_vertex_colors;
}

const std::vector<glm::vec2>& CgCube:: getVertexTexCoords() const
{
    return m_tex_coords;
}

const std::vector<unsigned int>& CgCube::getTriangleIndices() const
{
    return m_triangle_indices;
}

const std::vector<glm::vec3>& CgCube::getFaceNormals() const
{
    return m_face_normals;
}

const std::vector<glm::vec3>& CgCube::getFaceColors() const
{
    return m_face_colors;
}
