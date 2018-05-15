#include "CgZylinder.h"


CgZylinder::CgZylinder():
m_type(Cg::TriangleMesh),
m_counter(new CgIdCounter),
m_id(m_counter->getId())
{
    currentRes = 0.05;
    layers = 1;
    setResolution(currentRes, layers);


    for(unsigned int i = 0; i < m_vertices.size(); i++){
        cylinder_vert.push_back(glm::vec4(m_vertices[i].x,m_vertices[i].y,m_vertices[i].z,1));
    }


}

CgZylinder::~CgZylinder(){
    m_vertices.clear();
    m_vertex_normals.clear();
    m_vertex_colors.clear();
    m_tex_coords.clear();
    m_triangle_indices.clear();
    m_face_normals.clear();
    m_face_colors.clear();
    cylinder_vert.clear();
    m_normals.clear();
}

void CgZylinder::createBaseAreas(glm::vec3 mitte, bool bot, float res){
    m_vertices.push_back(mitte);
    unsigned int index_mitte = m_vertices.size()-1;
    for(float i = 0; i < 2*M_PI; i = i + res){
        //Folie F376
        m_vertices.push_back(glm::vec3((RADIUS*cos(i)),(mitte.y + RADIUS * sin(i)), mitte.z));
    }
    //Decke
    if(!bot){
        for(unsigned int i = index_mitte; i < m_vertices.size()-1; i++){
            m_triangle_indices.push_back(index_mitte);
            m_triangle_indices.push_back(i);
            m_triangle_indices.push_back(i+1);
            }
        m_triangle_indices.push_back(index_mitte);
        m_triangle_indices.push_back(m_vertices.size()-1);
        m_triangle_indices.push_back(index_mitte+1);
    }
    //Boden
    else if(bot){
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

void CgZylinder::connectTop(){
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

void CgZylinder::createSurface(float layers){
    int indexLayerZwei;
    size = m_vertices.size()-1;
    float layerDistance = 1/(layers+1.f);
    //Punkte der aller Layers erzeugen
    for(int j = 0; j < layers; j++,layerDistance = layerDistance + 1/(layers+1.f)){
    for(unsigned int i = 1; i <= size; i++){
        m_vertices.push_back(glm::vec3(m_vertices[i].x,m_vertices[i].y,m_vertices[i].z + layerDistance));
    }
    }

    //Punkte aller Layer verbinden
    //Durchlauf m_vertices pro Layer
    for(unsigned int i = 1; i < m_vertices.size() - size; i = i + size){
        indexLayerZwei = i + size;
        //verbindet alle punkte zweier Layers
        for( unsigned int indexLayerEins = i; indexLayerEins < i +size - 1; indexLayerEins++, indexLayerZwei++){


                m_triangle_indices.push_back(indexLayerEins);
                m_triangle_indices.push_back(indexLayerZwei+1);
                m_triangle_indices.push_back(indexLayerZwei);

                m_triangle_indices.push_back(indexLayerEins);
                m_triangle_indices.push_back(indexLayerEins+1);
                m_triangle_indices.push_back(indexLayerZwei+1);


        }
        //Punkt n mit 1 verbinden
        m_triangle_indices.push_back(i + size -1);
        m_triangle_indices.push_back(i + size);
        m_triangle_indices.push_back(i + 2*size -1);

        m_triangle_indices.push_back(i + size -1);
        m_triangle_indices.push_back(i);
        m_triangle_indices.push_back(i + size);
    }

}


//Berechnet alle Normalen für jedes Dreieck des Würfels und speichert diese als CgMyPolyline im Vector m.normals.
void CgZylinder::calcNormals(){
    int j = 2;
    for(unsigned int i = 0; i < m_triangle_indices.size(); i = i + 3,j++){
        m_normals.push_back(new CgMyPolyline(calcPinpoint(m_vertices[m_triangle_indices[i]],m_vertices[m_triangle_indices[i+1]],m_vertices[m_triangle_indices[i+2]]),calcCross(m_vertices[m_triangle_indices[i]],m_vertices[m_triangle_indices[i+1]],m_vertices[m_triangle_indices[i+2]])));
    }
}


std::vector<CgMyPolyline*> CgZylinder::getNormals(){
    return m_normals;
}

//Berechnet den Schwerpunkt eines übergebenen Dreiecks. Übergabe des Dreiecks erfolgt durch die drei Eckpunkte.
glm::vec3 CgZylinder::calcPinpoint(glm::vec3 zero, glm::vec3 one, glm::vec3 two){
    glm::vec3 test;
    test = zero += one;
    test += two;
    test = glm::vec3(test.x*1/3,test.y*1/3,test.z*1/3);

    return test;

}

//Berechnet die Normalen-Ausrichtung eines übergebenen Dreiecks. Übergabe des Dreiecks erfolgt durch die drei Eckpunkte.
glm::vec3 CgZylinder::calcCross(glm::vec3 zero, glm::vec3 one, glm::vec3 two){
    return (glm::cross((two -= one), (zero -= one)));

}
void CgZylinder::setLayers(float value){
    layers = value;
    setResolution(currentRes, layers);
}

void CgZylinder::setLayerResolution(float res){
    currentRes = res;
    setResolution(currentRes, layers);
}

void CgZylinder::setResolution(float res, float layers){
    m_vertices.clear();
    m_triangle_indices.clear();
    m_normals.clear();
    createBaseAreas(glm::vec3(0,0,-0.5), true, res);
    createSurface(layers);
    createBaseAreas(glm::vec3(0,0,0.5),false, res);
    connectTop();

    calcNormals();

}

const std::vector<glm::vec3>& CgZylinder::getVertices()const{
    return m_vertices;
}

 const std::vector<glm::vec3>& CgZylinder::getVertexNormals()const{
    return m_vertex_normals;
}

const std::vector<glm::vec3>& CgZylinder::getVertexColors()const{
    return m_vertex_colors;
}

const std::vector<glm::vec2>& CgZylinder::getVertexTexCoords()const{
    return m_tex_coords;
}

// ein Dreieck hat immer 3 Indices, also ist die Index-Liste 3 mal so lang wie die Anzahl der Dreiecke
 const std::vector<unsigned int>& CgZylinder::getTriangleIndices()const{
     return m_triangle_indices;
 }

// Es gibt so viele Face-Normalen wie Polygone/Dreiecke, da ein Face als planar angenommen wird und daher genau eine Normale hat.
const std::vector<glm::vec3>& CgZylinder::getFaceNormals() const{
    return m_face_normals;
}

// Falls eine Farbe pro Polygon spezifiziert ist, so ist es einfarbig in genau dieser Farbe, also auch #Farben=#Faces
const std::vector<glm::vec3>& CgZylinder::getFaceColors() const{
    return m_face_colors;
}


