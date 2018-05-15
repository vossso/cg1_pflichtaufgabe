


#include "CgQtGLRenderWidget.h"
#include "CgQtGlBufferObject.h"

#include "CgBase/CgBasePolyline.h"
#include "CgBase/CgBasePolygonMesh.h"

#include "CgBase/CgBaseRenderableObject.h"
#include "CgBase/CgEnums.h"
#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QCoreApplication>
#include <math.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>
#include <iostream>

#include "CgBase/CgBaseSceneControl.h"
#include "CgTrackball.h"

bool CgQtGLRenderWidget::m_transparent = false;

CgQtGLRenderWidget::CgQtGLRenderWidget(QWidget *parent)
    : QOpenGLWidget(parent),
      m_program(0),
      m_custom_rotation(false),
      m_lighting(false),
      m_scene_control(NULL),
      m_backface_culling(false),
      m_polygonmode(1)
{
    m_core = QSurfaceFormat::defaultFormat().profile() == QSurfaceFormat::CoreProfile;
    // --transparent causes the clear color to be transparent. Therefore, on systems that
    // support it, the widget will become transparent apart from the logo.
    if (m_transparent) {
        QSurfaceFormat fmt = format();
        fmt.setAlphaBufferSize(8);
        setFormat(fmt);
    }
}

CgQtGLRenderWidget::~CgQtGLRenderWidget()
{
    cleanup();
}

void CgQtGLRenderWidget::redraw()
{
    update();
}


QSize CgQtGLRenderWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize CgQtGLRenderWidget::sizeHint() const
{
    return QSize(400, 400);
}



void CgQtGLRenderWidget::cleanup()
{
    if (m_program == NULL)
        return;
    makeCurrent();
    delete m_program;
    m_program = 0;
    doneCurrent();
}

static const char *vertexShaderSourceCore =
    "#version 150\n"
    "in vec4 vertex;\n"
    "in vec3 normal;\n"
    "out vec3 vert;\n"
    "out vec3 vertNormal;\n"
    "uniform mat4 projMatrix;\n"
    "uniform mat4 mvMatrix;\n"
    "uniform mat3 normalMatrix;\n"
    "void main() {\n"
    "   vert = vertex.xyz;\n"
    "   vertNormal = normalMatrix * normal;\n"
    "   gl_Position = projMatrix * mvMatrix * vertex;\n"
    "}\n";

static const char *fragmentShaderSourceCore =
    "#version 150\n"
    "in highp vec3 vert;\n"
    "in highp vec3 vertNormal;\n"
    "out highp vec4 fragColor;\n"
    "uniform highp vec3 lightPos;\n"
    "void main() {\n"
    "   highp vec3 L = normalize(lightPos - vert);\n"
    "   highp float NL = max(dot(normalize(vertNormal), L), 0.0);\n"
    "   highp vec3 color = vec3(0.39, 1.0, 0.0);\n"
    "   highp vec3 col = clamp(color * 0.2 + color * 0.8 * NL, 0.0, 1.0);\n"
    "   fragColor = vec4(col, 1.0);\n"
    "}\n";

static const char *vertexShaderSource =
    "attribute vec4 vertex;\n"
    "attribute vec3 normal;\n"
    "varying vec3 vert;\n"
    "varying vec3 vertNormal;\n"
    "uniform mat4 projMatrix;\n"
    "uniform mat4 mvMatrix;\n"
    "uniform mat3 normalMatrix;\n"
    "void main() {\n"
    "   vert = vertex.xyz;\n"
    "   vertNormal = normalMatrix * normal;\n"
    "   gl_Position = projMatrix * mvMatrix * vertex;\n"
    "}\n";

static const char *fragmentShaderSource =
    "varying highp vec3 vert;\n"
    "varying highp vec3 vertNormal;\n"
    "uniform highp vec3 lightPos;\n"
    "uniform bool  calcLighting;\n"
    "uniform vec3 singlecolor;\n"
    "uniform bool use_single_color;\n"

    "void main() {\n"
    "   highp vec3 L = normalize(lightPos - vert);\n"
    "   highp float NL = max(dot(normalize(vertNormal), L), 0.0);\n"
    "   highp vec3 color;\n"
    "   if(use_single_color)\n"
    "   {\n "
    "      color=singlecolor;\n"
    "    }\n"
    "   else\n"
    "   {\n "
    "      color= vec3(0.39, 1.0, 0.0);\n"
    "    }\n"
    "   highp vec3 col = clamp(color * 0.2 + color * 0.8 * NL, 0.0, 1.0);\n"
    "   if(!calcLighting)\n"
    "      { col=color;} \n"
    "   gl_FragColor = vec4(col, 1.0);\n"
    "}\n";



void CgQtGLRenderWidget::render(CgBaseRenderableObject* obj,glm::mat4 world_coordinates)
{
    m_world=world_coordinates;


    // here arcball rotation

    if(!m_custom_rotation)
    {
        glm::mat4 arc_rot= m_trackball->getRotationMatrix();
        m_world = arc_rot* m_world ;
    }

    if(m_lighting)
    {
        std::cout << "light on" << std::endl;
    }

    glm::mat4 mv_matrix = m_lookat * m_world ;
    glm::mat3 normal_matrix = glm::transpose(glm::inverse(glm::mat3(mv_matrix)));


    m_program->setUniformValue(m_projMatrixLoc, QMatrix4x4(glm::value_ptr(m_proj)).transposed());
    m_program->setUniformValue(m_mvMatrixLoc, QMatrix4x4(glm::value_ptr(mv_matrix)).transposed());
    m_program->setUniformValue(m_normalMatrixLoc, QMatrix3x3(glm::value_ptr(normal_matrix)));
    m_program->setUniformValue(m_lightPosLoc,QVector3D(m_light_pos.x,m_light_pos.y,m_light_pos.z));
    m_program->setUniformValue(m_calcLightingLoc,m_lighting);


    if(obj->getType()==Cg::Polyline)
    {
      CgBasePolyline* c_obj=(CgBasePolyline*)obj;
      m_program->setUniformValue(m_ColorLoc,QVector3D(c_obj->getColor().x,c_obj->getColor().y,c_obj->getColor().z));
      m_program->setUniformValue(m_UseSingleColorLoc,true);
    }


    if(obj->getType()==Cg::TriangleMesh)
    {
      m_program->setUniformValue(m_UseSingleColorLoc,false);
      glLineWidth(1.0f);
    }



    if(m_gl_buffer_objects.find(obj->getID())!=m_gl_buffer_objects.end())
    {
         m_gl_buffer_objects[obj->getID()]->draw(obj);
    }


}


void CgQtGLRenderWidget::setLookAtMatrix(glm::mat4 lookat)
{
    m_lookat=lookat;
}

void CgQtGLRenderWidget::setProjectionMatrix(glm::mat4 proj)
{
   m_proj=proj;
}


void CgQtGLRenderWidget::init(CgBaseRenderableObject* obj)
{
    CgQtGlBufferObject* bobj;

    if(m_gl_buffer_objects.find(obj->getID())!=m_gl_buffer_objects.end())
        bobj = m_gl_buffer_objects[obj->getID()];
    else
        bobj = new CgQtGlBufferObject(m_program);



    if(obj->getType()==Cg::TriangleMesh)
    {
        bobj->initTriangleMesh((CgBaseTriangleMesh*)obj);
    }
    if(obj->getType()==Cg::PolygonalMesh)
    {
        bobj->initPolygonMesh((CgBasePolygonMesh*)obj);
    }
    if(obj->getType()==Cg::Polyline)
    {
        bobj->initPolyline((CgBasePolyline*)obj);
    }
    if(obj->getType()==Cg::PointCloud)
    {
        bobj->initPointCloud((CgBasePointCloud*)obj);
    }

    m_gl_buffer_objects.insert(std::make_pair(obj->getID(),bobj));
}




void CgQtGLRenderWidget::initializeGL()
{


    m_trackball = new CgTrackball();
    m_trackball->init();
    m_trackball->place(glm::vec3(0.0,0.0,0.0),0.75);


    // In this example the widget's corresponding top-level window can change
    // several times during the widget's lifetime. Whenever this happens, the
    // QOpenGLWidget's associated context is destroyed and a new one is created.
    // Therefore we have to be prepared to clean up the resources on the
    // aboutToBeDestroyed() signal, instead of the destructor. The emission of
    // the signal will be followed by an invocation of initializeGL() where we
    // can recreate all resources.
    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &CgQtGLRenderWidget::cleanup);

    initializeOpenGLFunctions();

    glFrontFace(GL_CCW);
    glClearColor(0, 0, 0, m_transparent ? 0 : 1);


    m_program = new QOpenGLShaderProgram;
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, m_core ? vertexShaderSourceCore : vertexShaderSource);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, m_core ? fragmentShaderSourceCore : fragmentShaderSource);
    m_program->bindAttributeLocation("vertex", 0);
    m_program->bindAttributeLocation("normal", 1);
    m_program->link();

    m_program->bind();
    
    
    m_projMatrixLoc = m_program->uniformLocation("projMatrix");
    m_mvMatrixLoc = m_program->uniformLocation("mvMatrix");
    m_normalMatrixLoc = m_program->uniformLocation("normalMatrix");
    m_lightPosLoc = m_program->uniformLocation("lightPos");
    m_calcLightingLoc = m_program->uniformLocation("calcLighting");
    m_ColorLoc = m_program->uniformLocation("singlecolor");
    m_UseSingleColorLoc = m_program->uniformLocation("use_single_color");



    // Our camera never changes in this example.
    m_lookat=glm::lookAt(glm::vec3(0.0,0.0,1.0),glm::vec3(0.0,0.0,0.0),glm::vec3(0.0,1.0,0.0));

    m_world=glm::mat4(1.);


    // Light position is fixed.
    m_light_pos=glm::vec3(0.0,0.0,70.0);
    m_program->release();
}



void CgQtGLRenderWidget::paintGL()
{


    switch(m_polygonmode)
    {
    case 0: glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        break;
    case 1: glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        break;
    case 2: glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        break;
     default: break;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    m_program->bind();

    if(m_scene_control!=NULL)
    m_scene_control->renderObjects();



    m_program->release();

}

void CgQtGLRenderWidget::resizeGL(int w, int h)
{
    emit viewportChanged(w,h);
}

void CgQtGLRenderWidget::mousePressEvent(QMouseEvent *event)
{
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT,viewport);
    GLfloat w=(GLfloat)viewport[2];
    GLfloat h=(GLfloat)viewport[3];

    float x= (float)event->x();
    float y= (float)event->y();


    // normalize into [-1;1]
    x=2.0*x / w -1.0;
    if (x<-1.0) x=-1.0;
    if (x>1.0) x=1.0;

    y=2.0*y / h -1.0;
    if (y<-1.0) y=-1.0;
    if (y>1.0) y=1.0;

    if(event->button()&Qt::LeftButton)
    {
        m_trackball->Ball_Mouse(glm::vec3(x,-y,0.0));
        m_trackball->beginDrag();
    }

    emit mouseEvent(event);
    update();
}

void CgQtGLRenderWidget::mouseMoveEvent(QMouseEvent *event)
{

    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT,viewport);
    GLfloat w=(GLfloat)viewport[2];
    GLfloat h=(GLfloat)viewport[3];

    float x= (float)event->x();
    float y= (float)event->y();


    // normalize into [-1;1]
    x=2.0*x / w -1.0;
    if (x<-1.0) x=-1.0;
    if (x>1.0) x=1.0;

    y=2.0*y / h -1.0;
    if (y<-1.0) y=-1.0;
    if (y>1.0) y=1.0;

    m_trackball->Ball_Mouse(glm::vec3(x,-y,0.0));
    m_trackball->Ball_Update();

    emit mouseEvent(event);

       update();
}


void CgQtGLRenderWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()&Qt::LeftButton)
    {
     m_trackball->endDrag();

    }
     emit mouseEvent(event);
     update();
}



void CgQtGLRenderWidget::slotCustomRotation()
{
     m_custom_rotation=!m_custom_rotation;
      update();
}

void CgQtGLRenderWidget::slotLighting()
{
    m_lighting=!m_lighting;
     update();
}


void CgQtGLRenderWidget::slotPolygonPoints()
{
    m_polygonmode=0;
     update();
}


void CgQtGLRenderWidget::slotPolygonWireframe()
{
    m_polygonmode=1;
     update();
}

void CgQtGLRenderWidget::slotPolygonFilled()
{
   m_polygonmode=2;
    update();
}




