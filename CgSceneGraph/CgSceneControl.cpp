#include "CgSceneControl.h"
#include "CgBase/CgEnums.h"
#include "CgEvents/CgMouseEvent.h"
#include "CgEvents/CgKeyEvent.h"
#include "CgEvents/CgWindowResizeEvent.h"
#include "CgBase/CgBaseRenderer.h"
#include "CgExampleTriangle.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "CgEvents/CgSliderChangeEvent.h"
#include "CgEvents/CgSpinboxEvent.h"
#include "CgEvents/CgCheckBoxEvent.h"

CgSceneControl::CgSceneControl()
{
    CgMyPolyline* test;

    //Würfel Objekt erzeugen.
    m_cylinder = new CgZylinder();
    //m_cone = new CgCone(1);
    // m_cube = new CgCube(1);
     //Normalen über den Würfel abfragen.
    //m_normals = m_cylinder->getNormals();

    /* m_current_transformation=glm::mat4(1.);
     for(int i = 0; i < m_normals.size(); i++){
         test = m_normals[i];
    std::cout<< test->getID() << std::endl;
     }*/
     m_proj_matrix= glm::mat4x4(glm::vec4(1.792591, 0.0, 0.0, 0.0), glm::vec4(0.0, 1.792591, 0.0, 0.0), glm::vec4(0.0, 0.0, -1.0002, -1.0), glm::vec4(0.0, 0.0, -0.020002, 0.0));
}




CgSceneControl::~CgSceneControl()
{
    for(unsigned int i = 0; i < m_normals.size(); i++){
        delete m_normals[i];
    }

    // delete m_cube;
    delete m_cylinder;
    //delete m_cone;
}

void CgSceneControl::setRenderer(CgBaseRenderer* r)
{
    m_renderer=r;
    m_renderer->setSceneControl(this);

    m_renderer->init(m_cylinder);
   // m_renderer->(m_cone);
   // m_renderer->init(m_cube);

    for(unsigned int i = 0; i < m_normals.size(); i++){
        m_renderer->init(m_normals[i]);
    }
}


void CgSceneControl::renderObjects()
{
    m_renderer->setProjectionMatrix(m_proj_matrix);
    m_renderer->setLookAtMatrix(glm::mat4x4(glm::vec4(1.0, 0.0, 0.0, 0.0), glm::vec4(0.0, 1.0, 0.0, 0.0), glm::vec4(0.0, 0.0, 1.0, -1.0), glm::vec4(0.0, 0.0, -1.0, 1.0)));
    m_renderer->render(m_cylinder,m_current_transformation);

   // m_renderer->render(m_cone,m_current_transformation);
   // m_renderer->render(m_cube,m_current_transformation);
   for(unsigned int i = 0; i < m_normals.size(); i++){
        m_renderer->render(m_normals[i], m_current_transformation);
    }
}



void CgSceneControl::handleEvent(CgBaseEvent* e)
{
    // die Enums sind so gebaut, dass man alle Arten von MausEvents über CgEvent::CgMouseEvent abprüfen kann,
    // siehe dazu die CgEvent enums im CgEnums.h


    if(e->getType() & Cg::CgMouseEvent)
    {
        CgMouseEvent* ev = (CgMouseEvent*)e;
        std::cout << *ev << std::endl;

         // hier kommt jetzt die Abarbeitung des Events hin...
    }

    // die Enums sind so gebaut, dass man alle Arten von KeyEvents über CgEvent::CgKeyEvent abprüfen kann,
    // siehe dazu die CgEvent enums im CgEnums.h
    // momentan werden nur KeyPressEvents gefangen.

    if(e->getType() & Cg::CgKeyEvent)
    {
        CgKeyEvent* ev = (CgKeyEvent*)e;
        std::cout << *ev <<std::endl;

        // hier kommt jetzt die Abarbeitung des Events hin...
    }

    if(e->getType() & Cg::WindowResizeEvent)
    {
         CgWindowResizeEvent* ev = (CgWindowResizeEvent*)e;
         std::cout << *ev <<std::endl;
         m_proj_matrix=glm::perspective(45.0f, (float)(ev->w()) / ev->h(), 0.01f, 100.0f);
    }

    //Spinbox für Anzahl der Ebenen
    if(e->getType() & Cg::CgSpinboxEvent){
        CgSpinboxEvent* ev = (CgSpinboxEvent*)e;
        m_cylinder->setLayers(ev->getValue());
        m_normals = m_cylinder->getNormals();
        m_renderer->init(m_cylinder);
        for(unsigned int i = 0; i < m_normals.size(); i++){
            m_renderer->init(m_normals[i]);
        }
        m_renderer->redraw();

    }
    //Normalen an/aus
    if(e->getType() & Cg::CgCheckBoxEvent){

        if(normals_check){
            m_normals = m_cylinder->getNormals();
            for(unsigned int i = 0; i < m_normals.size(); i++){
                m_renderer->init(m_normals[i]);
            }
            normals_check = false;
        }else if(!normals_check){
            m_normals.clear();
            normals_check = true;
        }
        //m_renderer->init(m_cylinder);
        m_renderer->redraw();
    }

    //Abarbeitung bei Auftreten eines ColorChanEvents(SliderEvents).
    if(e->getType() & Cg::CgSliderChangeEvent)
    {

     CgSliderChangeEvent* ev = (CgSliderChangeEvent*)e;

     //Slider Rot
     if(ev->getSlider() & Cg::rSlider){
         std::cout << "Rotwert: " << ev->getColor() << std::endl;
         for(unsigned int i = 0; i < m_normals.size(); i++){
             m_normals[i]->setColorRed(ev->getColor());
         }
     }

     //Slider Grün
     else if(ev->getSlider() & Cg::gSlider){
         std::cout << "Gruenwert: " << ev->getColor() << std::endl;
         for(unsigned int i = 0; i < m_normals.size(); i++){
             m_normals[i]->setColorGreen(ev->getColor());
         }
     }


     //Slider Blau
     else if(ev->getSlider() & Cg::bSlider){
         std::cout << "Blauwert: " << ev->getColor() << std::endl;
         for(unsigned int i = 0; i < m_normals.size(); i++){
             m_normals[i]->setColorBlue(ev->getColor());
         }
     }else if(ev->getSlider() & Cg::hight){
         m_current_transformation[2][2] = 0.25 * ev->getColor();
     }else if(ev->getSlider() & Cg::width){
         //std::cout <<  m_current_transformation[0][0] << " current mat 0]"<< std::endl;
         m_current_transformation[0][0]= 0.25 * ev->getColor();
         m_current_transformation[1][1]= 0.25* ev->getColor();
     }//Slider zur Auflösung der Kreisrotation
     else if(ev->getSlider() & Cg::resolution){
         m_cylinder->setLayerResolution(0.05 * (ev->getColor()));
         m_normals = m_cylinder->getNormals();
         m_renderer->init(m_cylinder);
         for(unsigned int i = 0; i < m_normals.size(); i++){
             m_renderer->init(m_normals[i]);
         }

     }

     //   m_cylinder->resizeWidth(5);
        //Szene neu zeichnen nach Farbänderung.
        m_renderer->redraw();
    }
    // an der Stelle an der ein Event abgearbeitet ist wird es auch gelöscht.
    delete e;


}
