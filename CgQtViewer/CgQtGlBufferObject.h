#ifndef CGQTGLBUFFEROBJECT_H
#define CGQTGLBUFFEROBJECT_H


class CgBasePolyline;
class CgBaseTriangleMesh;
class CgBasePolygonMesh;
class CgBasePointCloud;
class CgBaseRenderableObject;

#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>

class CgQtGlBufferObject
{
public:
    CgQtGlBufferObject();
    CgQtGlBufferObject(QOpenGLShaderProgram *);


    QOpenGLVertexArrayObject m_object;
    QOpenGLBuffer m_vertices;
    QOpenGLBuffer m_normals;
    QOpenGLBuffer m_face_indices;

    QOpenGLShaderProgram *m_program;

    void draw(CgBaseRenderableObject*);

    int m_vert_size;
    int m_face_indices_size;

    void initPolyline(CgBasePolyline* obj);
    void initTriangleMesh(CgBaseTriangleMesh* obj);
    void initPolygonMesh(CgBasePolygonMesh* obj);
    void initPointCloud(CgBasePointCloud* obj);

private:

    void drawPolyline(CgBasePolyline* obj);
    void drawTriangleMesh(CgBaseTriangleMesh* obj);
    void drawPolygonMesh(CgBasePolygonMesh* obj);
    void drawPointCloud(CgBasePointCloud* obj);

};

#endif // CGQTGLBUFFEROBJECT_H
