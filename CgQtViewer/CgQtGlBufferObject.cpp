#include "CgQtGlBufferObject.h"
#include "CgBase/CgBasePolyline.h"
#include "CgBase/CgBasePolygonMesh.h"
#include "CgBase/CgBaseTriangleMesh.h"
#include "CgBase/CgBasePointCloud.h"

CgQtGlBufferObject::CgQtGlBufferObject():
    m_vert_size(0)
{
    /*m_program = new QOpenGLShaderProgram();
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/simple.vert");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/simple.frag");
    m_program->link();*/
}


CgQtGlBufferObject::CgQtGlBufferObject(QOpenGLShaderProgram* program):
m_face_indices(QOpenGLBuffer::IndexBuffer),
m_vert_size(0)
{
    m_program = program;
}


void CgQtGlBufferObject::initPolyline(CgBasePolyline* obj)
{

    if(m_vert_size!=0)
    {
        m_vert_size=0;
        m_vertices.destroy();
        m_object.destroy();
    }




    m_vert_size = obj->getVertices().size();


    // Create Buffer (Do not release until VAO is created)
    m_vertices.create();
    m_vertices.bind();
    m_vertices.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vertices.allocate(obj->getVertices().data(), m_vert_size* sizeof(glm::vec3));




}



void CgQtGlBufferObject::initTriangleMesh(CgBaseTriangleMesh* obj)
{


    if(m_vert_size!=0)
    {
        m_vert_size=0;
        m_vertices.destroy();
        m_normals.destroy();
        m_object.destroy();
        m_face_indices.destroy();
    }


    m_vert_size = obj->getVertices().size();

    // Create Buffer (Do not release until VAO is created)
    m_vertices.create();
    m_vertices.bind();
    m_vertices.allocate(obj->getVertices().data(), m_vert_size* sizeof(glm::vec3));

    m_normals.create();
    m_normals.bind();
    m_normals.allocate(obj->getVertexNormals().data(), m_vert_size* sizeof(glm::vec3));

    m_face_indices_size=obj->getTriangleIndices().size();
    m_face_indices.create();
    m_face_indices.bind();
    m_face_indices.allocate(obj->getTriangleIndices().data(), m_face_indices_size* sizeof(unsigned int));

}

void CgQtGlBufferObject::initPolygonMesh(CgBasePolygonMesh* obj)
{
    m_vert_size = obj->getVertices().size();
    // do something more
}

void CgQtGlBufferObject::initPointCloud(CgBasePointCloud* obj)
{
    m_vert_size = obj->getVertices().size();
    // do something more
}

void CgQtGlBufferObject::draw(CgBaseRenderableObject* obj)
{

    if(obj->getType()==Cg::TriangleMesh)
        drawTriangleMesh((CgBaseTriangleMesh*) obj);
    if(obj->getType()==Cg::PolygonalMesh)
        drawPolygonMesh((CgBasePolygonMesh*) obj);
    if(obj->getType()==Cg::Polyline)
        drawPolyline((CgBasePolyline*)obj);
    if(obj->getType()==Cg::PointCloud)
        drawPointCloud((CgBasePointCloud*) obj);
}

void CgQtGlBufferObject::drawTriangleMesh(CgBaseTriangleMesh* obj)
{

    if(obj->getVertices().size()!=0)
    {
        m_vertices.bind();
        m_program->enableAttributeArray(0);
        m_program->setAttributeBuffer(0, GL_FLOAT, 0, 3 , sizeof(glm::vec3));
    }

    if(obj->getVertexNormals().size()!=0)
    {
        m_normals.bind();
        m_program->enableAttributeArray(1);
        m_program->setAttributeBuffer(1, GL_FLOAT, 0, 3 , sizeof(glm::vec3));
    }

    if(obj->getTriangleIndices().size()!=0)
    {
         m_face_indices.bind();
        glLineWidth(1.0);
        glDrawElements(GL_TRIANGLES,m_face_indices_size, GL_UNSIGNED_INT,0);
    }
}


void CgQtGlBufferObject::drawPolyline(CgBasePolyline* obj)
{
    m_vertices.bind();
    m_program->enableAttributeArray(0);
    m_program->setAttributeBuffer(0, GL_FLOAT, 0, 3 , sizeof(glm::vec3));


    glLineWidth((GLfloat) obj->getLineWidth());
    glDrawArrays(GL_LINE_STRIP,0,m_vert_size);
}


void CgQtGlBufferObject::drawPolygonMesh(CgBasePolygonMesh* obj)
{
    if(obj->getVertices().size()!=0)
    {
        // do something
    }
}

void CgQtGlBufferObject::drawPointCloud(CgBasePointCloud* obj)
{
    if(obj->getVertices().size()!=0)
    {
        // do something
    }
}









