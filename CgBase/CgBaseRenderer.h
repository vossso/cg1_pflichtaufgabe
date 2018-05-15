#ifndef CGBASERENDERER
#define CGBASERENDERER

#include <glm/glm.hpp>
class CgBaseRenderableObject;
class CgBaseSceneControl;

class CgBaseRenderer
{


    public:
        virtual void render(CgBaseRenderableObject*,glm::mat4 world_coordinates)=0;
        virtual void init(CgBaseRenderableObject*)=0;
        virtual void setLookAtMatrix(glm::mat4 lookat)=0;
        virtual void setProjectionMatrix(glm::mat4 proj)=0;
        virtual void setSceneControl(CgBaseSceneControl*)=0;
    
        virtual void redraw()=0;
};








#endif // CGBASERENDERER

