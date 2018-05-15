#include "CgCone.h"

CgCone::CgCone(unsigned int id):
m_type(Cg::TriangleMesh),
m_id(id)
{
    currentRes = 0.05;
    layers = 1;
    //createBase(glm::vec3(0,0,-0.5),true,1);
   // createBase(glm::vec3(0,0,0.5),false,1);
    createSurface(1);
    /*createBase(glm::vec3(0,0,-0.5),true,1);
    createSurface(1);
    createBase(glm::vec3(0,0,0.5),false, 1);
    connectTop();
    calcNormals();*/
    for(unsigned int i = 0; i < m_vertices.size(); i++){
        cylinder_vert.push_back(glm::vec4(m_vertices[i].x,m_vertices[i].y,m_vertices[i].z,1));
    }

    /*
    glm::mat4 test = glm::mat4(1.0f);
    test[0] = glm::vec4(cos(radius),-sin(radius),0,0);
    test[1] = glm::vec4(sin(radius),cos(radius),1,0);
    std::vector<glm::vec4> spasst;

    for(int i = 0; i < 8; i++){
       glm::mat4 test2 = test;

       spasst[i] = test2 * spasst[i];

        testvec.push_back(glm::vec3(spasst[i].x,spasst[i].y,spasst[i].z));
    }
    m_vertices = testvec;
    */
}

CgCone::~CgCone(){
    m_vertices.clear();
    m_vertex_normals.clear();
    m_vertex_colors.clear();
    m_tex_coords.clear();
    m_triangle_indices.clear();
    m_face_normals.clear();
    m_face_colors.clear();
    cylinder_vert.clear();
}

void CgCone::createBase(glm::vec3 mitte, bool bot, float res){


    if(!bot){
        m_vertices.push_back(mitte);
        unsigned int index_mitte = m_vertices.size()-1;
        for(float i = 0; i < 2*M_PI; i = i + res){
            m_vertices.push_back(glm::vec3((RADIUS*cos(i)),(mitte.y + RADIUS * sin(i)), mitte.z));
        }
        for(unsigned int i = index_mitte; i < m_vertices.size()-1; i++){
            m_triangle_indices.push_back(index_mitte);
            m_triangle_indices.push_back(i);
            m_triangle_indices.push_back(i+1);
            }
        m_triangle_indices.push_back(index_mitte);
        m_triangle_indices.push_back(m_vertices.size()-1);
        m_triangle_indices.push_back(index_mitte+1);
    }else if(bot){
        m_vertices.push_back(mitte);
        unsigned int index_mitte = m_vertices.size()-1;
        for(float i = 0; i < 2*M_PI; i = i + res){
            m_vertices.push_back(glm::vec3((0.2 *cos(i)),( 0.2 * sin(i)), mitte.z));
        }
        for(unsigned int i = index_mitte; i < m_vertices.size()-1; i++){
            m_triangle_indices.push_back(index_mitte);
            m_triangle_indices.push_back(i+1);
            m_triangle_indices.push_back(i);
            }
        m_triangle_indices.push_back(index_mitte);
        m_triangle_indices.push_back(index_mitte+1);
        m_triangle_indices.push_back(m_vertices.size()-1);
    }


}

void CgCone::connectTop(){
    int indexZwei = m_vertices.size() -size;
    unsigned int indexEins;
    for(indexEins = m_vertices.size() -2*size -1; indexEins < m_vertices.size() - size-2; indexEins++, indexZwei++){


            m_triangle_indices.push_back(indexEins);
            m_triangle_indices.push_back(indexZwei+1);
            m_triangle_indices.push_back(indexZwei);

            m_triangle_indices.push_back(indexEins);
            m_triangle_indices.push_back(indexEins+1);
            m_triangle_indices.push_back(indexZwei+1);


    }

    m_triangle_indices.push_back(m_vertices.size() -size -2);
    m_triangle_indices.push_back(m_vertices.size() -size );
    m_triangle_indices.push_back(m_vertices.size() -1);

    m_triangle_indices.push_back(m_vertices.size() -size -2);
    m_triangle_indices.push_back(m_vertices.size() -2*size -1 );
    m_triangle_indices.push_back(m_vertices.size() -size);
}

void CgCone::createSurface(float layers){
    int indexZwei;
    size = m_vertices.size()-1;
    float paramH = 1/(layers+1.f);
    float test = 0;
    for(int j = 0; j < layers; j++,paramH = paramH + 1/(layers+1.f),test++){
    for(unsigned int i = 1; i <= size; i++){
        m_vertices.push_back(glm::vec3((RADIUS-paramH * cos(test)),(RADIUS-paramH)*sin(test),(m_vertices[i].z + paramH)));
    }
    }

    for(unsigned int i = 1; i < m_vertices.size() - size; i = i + size){
        indexZwei = i + size;
        for( unsigned int indexEins = i; indexEins < i +size - 1; indexEins++, indexZwei++){


                m_triangle_indices.push_back(indexEins);
                m_triangle_indices.push_back(indexZwei+1);
                m_triangle_indices.push_back(indexZwei);

                m_triangle_indices.push_back(indexEins);
                m_triangle_indices.push_back(indexEins+1);
                m_triangle_indices.push_back(indexZwei+1);


        }

        m_triangle_indices.push_back(i + size -1);
        m_triangle_indices.push_back(i + size);
        m_triangle_indices.push_back(i + 2*size -1);

        m_triangle_indices.push_back(i + size -1);
        m_triangle_indices.push_back(i);
        m_triangle_indices.push_back(i + size);
    }

}


//Berechnet alle Normalen für jedes Dreieck des Würfels und speichert diese als CgMyPolyline im Vector m.normals.
void CgCone::calcNormals(){
    int j = 2;
    for(unsigned int i = 0; i < m_triangle_indices.size(); i = i + 3,j++){
        m_normals.push_back(new CgMyPolyline( calcPinpoint(m_vertices[m_triangle_indices[i]],m_vertices[m_triangle_indices[i+1]],m_vertices[m_triangle_indices[i+2]]),calcCross(m_vertices[m_triangle_indices[i]],m_vertices[m_triangle_indices[i+1]],m_vertices[m_triangle_indices[i+2]])));
    }
}


std::vector<CgMyPolyline*> CgCone::getNormals(){
    return m_normals;
}

//Berechnet den Schwerpunkt eines übergebenen Dreiecks. Übergabe des Dreiecks erfolgt durch die drei Eckpunkte.
glm::vec3 CgCone::calcPinpoint(glm::vec3 zero, glm::vec3 one, glm::vec3 two){
    glm::vec3 test;
    test = zero += one;
    test += two;
    test = glm::vec3(test.x*1/3,test.y*1/3,test.z*1/3);

    return test;

}

//Berechnet die Normalen-Ausrichtung eines übergebenen Dreiecks. Übergabe des Dreiecks erfolgt durch die drei Eckpunkte.
glm::vec3 CgCone::calcCross(glm::vec3 zero, glm::vec3 one, glm::vec3 two){
    return (glm::cross((two -= one), (zero -= one)));

}
void CgCone::setLayers(float value){
    layers = value;
    setResolution(currentRes, layers);
}

void CgCone::setCurrentRes(float res){
    currentRes = res;
    setResolution(currentRes, layers);
}

void CgCone::setResolution(float res, float layers){
   // float bot = m_vertices[0].y;
    //float top = m_vertices[m_vertices.size()/2].y;
    m_vertices.clear();
    m_triangle_indices.clear();
    m_normals.clear();
    createBase(glm::vec3(0,0,-0.5), true, res);
    createSurface(layers);
    createBase(glm::vec3(0,0,0.5),false, res);
    connectTop();

    calcNormals();

}

const std::vector<glm::vec3>& CgCone::getVertices()const{
    return m_vertices;
}

 const std::vector<glm::vec3>& CgCone::getVertexNormals()const{
    return m_vertex_normals;
}

const std::vector<glm::vec3>& CgCone::getVertexColors()const{
    return m_vertex_colors;
}

const std::vector<glm::vec2>& CgCone::getVertexTexCoords()const{
    return m_tex_coords;
}

// ein Dreieck hat immer 3 Indices, also ist die Index-Liste 3 mal so lang wie die Anzahl der Dreiecke
 const std::vector<unsigned int>& CgCone::getTriangleIndices()const{
     return m_triangle_indices;
 }

// Es gibt so viele Face-Normalen wie Polygone/Dreiecke, da ein Face als planar angenommen wird und daher genau eine Normale hat.
const std::vector<glm::vec3>& CgCone::getFaceNormals() const{
    return m_face_normals;
}

// Falls eine Farbe pro Polygon spezifiziert ist, so ist es einfarbig in genau dieser Farbe, also auch #Farben=#Faces
const std::vector<glm::vec3>& CgCone::getFaceColors() const{
    return m_face_colors;
}
