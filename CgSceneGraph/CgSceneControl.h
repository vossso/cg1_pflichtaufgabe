#ifndef CGSCENECONTROL_H
#define CGSCENECONTROL_H

#include "CgBase/CgObserver.h"
#include "CgBase/CgBaseSceneControl.h"
#include <glm/glm.hpp>
#include "CgCube.h"
#include "CgMyPolyline.h"
#include "CgQtViewer/CgQtGLRenderWidget.h"
#include "CgSceneGraph/CgZylinder.h"
#include <iostream>
#include "CgSceneGraph/CgCone.h"

class CgBaseEvent;
class CgBaseRenderer;
class CgExampleTriangle;

class CgSceneControl : public CgObserver, public CgBaseSceneControl
{
public:
    CgSceneControl();
    ~CgSceneControl();
    void handleEvent(CgBaseEvent* e);
    void setRenderer(CgBaseRenderer* r);

    void renderObjects();


private:

    CgCone* m_cone;
    CgZylinder* m_cylinder;
    CgBaseRenderer* m_renderer;
    CgCube* m_cube;
    CgExampleTriangle* m_triangle;
    glm::mat4 m_current_transformation;
    glm::mat4 m_proj_matrix;
    std::vector<CgMyPolyline*> m_normals;
    bool normals_check = true;



};

#endif // CGSCENECONTROL_H
