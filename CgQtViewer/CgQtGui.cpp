

#include "CgQtGLRenderWidget.h"
#include "CgQtGui.h"
#include "CgQtMainApplication.h"
#include "../CgBase/CgEnums.h"
#include "../CgEvents/CgMouseEvent.h"
#include "../CgEvents/CgKeyEvent.h"
#include "../CgEvents/CgWindowResizeEvent.h"
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QPushButton>
#include <QDesktopWidget>
#include <QApplication>
#include <QMessageBox>
#include <QLabel>
#include <QSpinBox>
#include <QCheckBox>
#include <QPushButton>
#include <QGroupBox>
#include <QButtonGroup>
#include <QRadioButton>
#include <QMenuBar>
#include <QActionGroup>
#include <iostream>
#include "../CgEvents/CgSliderChangeEvent.h"
#include "CgEvents/CgSpinboxEvent.h"
#include "CgEvents/CgCheckBoxEvent.h"


CgQtGui::CgQtGui(CgQtMainApplication *mw)
    : m_mainWindow(mw)
{
    m_glRenderWidget = new CgQtGLRenderWidget;

    connect(m_glRenderWidget, SIGNAL(mouseEvent(QMouseEvent*)), this, SLOT(mouseEvent(QMouseEvent*)));
    connect(m_glRenderWidget, SIGNAL(viewportChanged(int,int)), this, SLOT(viewportChanged(int,int)));


    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *container = new QHBoxLayout;


    QWidget *opt = new QWidget;
    createOptionPanelExample1(opt);

    QWidget *otheropt = new QWidget;
    createOptionPanelExample2(otheropt);

    QTabWidget* m_tabs = new QTabWidget();
    m_tabs->addTab(opt,"&Uebung1");
    m_tabs->addTab(otheropt,"&Uebung2");
    container->addWidget(m_tabs);

    m_tabs->setMaximumWidth(400);

    container->addWidget(m_glRenderWidget);

    QWidget *w = new QWidget;
    w->setLayout(container);
    mainLayout->addWidget(w);

    setLayout(mainLayout);
    setWindowTitle(tr("Übung Computergrafik 1 -  SoSe 2018"));


    /* create Menu Bar */
    m_menuBar = new QMenuBar;
    QMenu *file_menu = new QMenu("&File" );
    file_menu->addAction("&Open Mesh Model", this, SLOT(slotLoadMeshFile()));
    // todo: Add Quit-Action
    m_menuBar->addMenu( file_menu );
    QMenu *settings_menu = new QMenu("&Setting" );
    QMenu *polygon_mode_menu = new QMenu("&Polygon Mode" );

    QAction* m_custom_rot=settings_menu->addAction("&Custom Rotations", m_glRenderWidget, SLOT(slotCustomRotation()));
    m_custom_rot->setCheckable(true);
    m_custom_rot->setChecked(false);

    QAction* m_lighting=settings_menu->addAction("&Lighting on", m_glRenderWidget, SLOT(slotLighting()));
    m_lighting->setCheckable(true);
    m_lighting->setChecked(false);


    QActionGroup* polygonmode_group = new QActionGroup(this);
    polygonmode_group->setExclusive(true);

    QAction* points=polygon_mode_menu->addAction("&Points", m_glRenderWidget, SLOT(slotPolygonPoints()));
    points->setCheckable(true);
    points->setChecked(false);


    QAction* wireframe=polygon_mode_menu->addAction("&Wireframe", m_glRenderWidget, SLOT(slotPolygonWireframe()));
    wireframe->setCheckable(true);
    wireframe->setChecked(true);

    QAction* filled=polygon_mode_menu->addAction("&Filled", m_glRenderWidget, SLOT(slotPolygonFilled()));
    filled->setCheckable(true);
    filled->setChecked(false);



    polygonmode_group->addAction(points);
    polygonmode_group->addAction(wireframe);
    polygonmode_group->addAction(filled);



    // todo: Add Quit-Action
    m_menuBar->addMenu( file_menu );
    m_menuBar->addMenu( settings_menu );
    m_menuBar->addMenu( polygon_mode_menu );


    m_mainWindow->setMenuBar(m_menuBar);

}

QSlider *CgQtGui::createSlider()
{
    QSlider *slider = new QSlider(Qt::Horizontal);
    slider->setRange(0, 360 * 16);
    slider->setSingleStep(16);
    slider->setPageStep(15 * 16);
    slider->setTickInterval(15 * 16);
    slider->setTickPosition(QSlider::TicksRight);
    return slider;
}






void CgQtGui::createOptionPanelExample1(QWidget* parent)
{

    QVBoxLayout *tab1_control = new QVBoxLayout();


    /*Example for using a label */

    QLabel *options_label = new QLabel("Options");
    tab1_control->addWidget(options_label);
    options_label->setAlignment(Qt::AlignCenter);

    /*Example for using a spinbox */

   /* mySpinBox1 = new QSpinBox();
    tab1_control->addWidget(mySpinBox1);
    mySpinBox1->setMinimum(1);
    mySpinBox1->setMaximum(50);
    mySpinBox1->setValue(3);
   // mySpinBox1->setSuffix("   suffix");
   // mySpinBox1->setPrefix("Prefix:  ");
    connect(mySpinBox1, SIGNAL(valueChanged(int) ), this, SLOT(slotMySpinBox1Changed()) );
    tab1_control->addWidget(mySpinBox1);
    */


    /*Example for using a checkbox */

    /*myCheckBox1 = new QCheckBox("enable Option 1");
    myCheckBox1->setCheckable(true);
    myCheckBox1->setChecked(false);
    connect(myCheckBox1, SIGNAL( clicked() ), this, SLOT(slotMyCheckBox1Changed()) );
    tab1_control->addWidget(myCheckBox1);

    */
    /*Example for using a button */

    /*QPushButton* myButton1 = new QPushButton("&drueck mich");
    tab1_control->addWidget(myButton1);

    connect(myButton1, SIGNAL( clicked() ), this, SLOT(slotMyButton1Pressed()) );


    */
    parent->setLayout(tab1_control);

    //Slider Rot anlegen.
    QLabel* rot = new QLabel();
    rot->setText("Rot");
    tab1_control->addWidget(rot);
    QSlider* sliderR = CgQtGui::createSlider();
    tab1_control->addWidget(sliderR);
    sliderR->setRange(0, 256);
    sliderR->setSingleStep(1);
    sliderR->setPageStep(10);
    sliderR->setTickInterval(10);
    connect(sliderR,SIGNAL(valueChanged(int) ), this, SLOT(slotChangeColorR(int)) );

    //Slider Grün anlegen
    QLabel* gruen = new QLabel();
    gruen->setText("Grün");
    tab1_control->addWidget(gruen);
    QSlider* sliderG = CgQtGui::createSlider();
    tab1_control->addWidget(sliderG);
    sliderG->setRange(0, 256);
    sliderG->setSingleStep(1);
    sliderG->setPageStep(10);
    sliderG->setTickInterval(10);
    connect(sliderG,SIGNAL(valueChanged(int) ), this, SLOT(slotChangeColorG(int)) );

    //slider Blau anlegen
    QLabel* blau = new QLabel();
    blau->setText("Blau");
    tab1_control->addWidget(blau);
    QSlider* sliderB = CgQtGui::createSlider();
    tab1_control->addWidget(sliderB);
    sliderB->setRange(0, 256);
    sliderB->setSingleStep(1);
    sliderB->setPageStep(10);
    sliderB->setTickInterval(10);
    connect(sliderB,SIGNAL(valueChanged(int) ), this, SLOT(slotChangeColorB(int)) );
}

void CgQtGui::createOptionPanelExample2(QWidget* parent)
{


    QVBoxLayout *tab2_control = new QVBoxLayout();
    QHBoxLayout *subBox = new QHBoxLayout();



    /*Example for using a button group */

    QGroupBox* myGroupBox = new QGroupBox("Radiobutton Group Example ");

   /* myButtonGroup = new QButtonGroup(subBox);
    myButtonGroup->setExclusive(true);

    QRadioButton* radiobutton1 = new QRadioButton( "&Option1");
    QRadioButton* radiobutton2 = new QRadioButton( "&Option2");
    QRadioButton* radiobutton3 = new QRadioButton( "&Option3");
    QRadioButton* radiobutton4 = new QRadioButton( "&Option4");
    QRadioButton* radiobutton5 = new QRadioButton( "&Option5");

    radiobutton2->setChecked(true);

    myButtonGroup->addButton(radiobutton1,0);
    myButtonGroup->addButton(radiobutton2,1);
    myButtonGroup->addButton(radiobutton3,2);
    myButtonGroup->addButton(radiobutton4,3);
    myButtonGroup->addButton(radiobutton5,4);
    */

    //Höhe anpassen
    QLabel* hight = new QLabel();
    hight->setText("Höhe anpassen");
    tab2_control->addWidget(hight);
    QSlider* sliderHight = CgQtGui::createSlider();
    tab2_control->addWidget(sliderHight);
    sliderHight->setRange(4, 20);
    sliderHight->setSingleStep(1);
    sliderHight->setPageStep(10);
    sliderHight->setTickInterval(10);
    connect(sliderHight,SIGNAL(valueChanged(int) ), this, SLOT(slotResizeHight(int)) );

    //Breite anpassen
    QLabel* width = new QLabel();
    width->setText("Breite anpassen");
    tab2_control->addWidget(width);
    QSlider* sliderWidth = CgQtGui::createSlider();
    tab2_control->addWidget(sliderWidth);
    sliderWidth->setRange(4, 20);
    sliderWidth->setSingleStep(1);
    sliderWidth->setPageStep(10);
    sliderWidth->setTickInterval(10);
    connect(sliderWidth,SIGNAL(valueChanged(int) ), this, SLOT(slotResizeWidth(int)) );

    //Layer Auflösung anpassen
    QLabel* res = new QLabel();
    res->setText("Auflösung");
    tab2_control->addWidget(res);
    QSlider* sliderRes = CgQtGui::createSlider();
    tab2_control->addWidget(sliderRes);
    sliderRes->setRange(1, 20);
    sliderRes->setSingleStep(1);
    sliderRes->setPageStep(10);
    sliderRes->setTickInterval(10);
    connect(sliderRes,SIGNAL(valueChanged(int) ), this, SLOT(slotResolution(int)) );

    //Layer Anzahl anpassen
    QLabel* lay = new QLabel();
    lay->setText("Layers");
    tab2_control->addWidget(lay);
    QSpinBox* layers = new QSpinBox();
    tab2_control->addWidget(layers);
    layers->setMinimum(1);
    layers->setMaximum(50);
    layers->setValue(1);
   // mySpinBox1->setSuffix("   suffix");
   // mySpinBox1->setPrefix("Prefix:  ");
    connect(layers, SIGNAL(valueChanged(int) ), this, SLOT(slotLayers(int)) );

    QCheckBox* normalCheckBox = new QCheckBox("Normalen ein/aus schalten");
    normalCheckBox->setCheckable(true);
    normalCheckBox->setChecked(false);
    connect(normalCheckBox, SIGNAL( clicked() ), this, SLOT(slotShowNormals()) );
    tab2_control->addWidget(normalCheckBox);

    tab2_control->addWidget(layers);

   /* QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(radiobutton1);
    vbox->addWidget(radiobutton2);
    vbox->addWidget(radiobutton3);
    vbox->addWidget(radiobutton4);
    vbox->addWidget(radiobutton5);
    vbox->addStretch(1);
    myGroupBox->setLayout(vbox);
    subBox->addWidget(myGroupBox);
    tab2_control->addLayout(subBox);

    connect(myButtonGroup, SIGNAL( buttonClicked(int) ), this, SLOT( slotButtonGroupSelectionChanged() ) );
    */
    parent->setLayout(tab2_control);

}

//Erzäugt ein RedSlider Event und benachrichtigt den Observer
void CgQtGui::slotChangeColorR(int value){
    float f = static_cast<float>(value);
    CgBaseEvent* e = new CgSliderChangeEvent(Cg::CgSliderChangeEvent, Cg::rSlider, f);
    notifyObserver(e);

}

//Erzäugt ein GreenSlider Event und benachrichtigt den Observer
void CgQtGui::slotChangeColorG(int value){
    float f = static_cast<float>(value);
    CgBaseEvent* e = new CgSliderChangeEvent(Cg::CgSliderChangeEvent, Cg::gSlider, f);
    notifyObserver(e);

}

//Erzäugt ein BlueSlider Event und benachrichtigt den Observer
void CgQtGui::slotChangeColorB(int value){
    float f = static_cast<float>(value);
    CgBaseEvent* e = new CgSliderChangeEvent(Cg::CgSliderChangeEvent, Cg::bSlider, f);
    notifyObserver(e);

}

void CgQtGui::slotResizeHight(int value){
    float f = static_cast<float>(value);
    CgBaseEvent* e = new CgSliderChangeEvent(Cg::CgSliderChangeEvent, Cg::hight, f);
    notifyObserver(e);
}

void CgQtGui::slotResizeWidth(int value){
    float f = static_cast<float>(value);
    CgBaseEvent* e = new CgSliderChangeEvent(Cg::CgSliderChangeEvent, Cg::width, f);
    notifyObserver(e);
}

void CgQtGui::slotResolution(int value){
    float f = static_cast<float>(value);
    CgBaseEvent* e = new CgSliderChangeEvent(Cg::CgSliderChangeEvent, Cg::resolution, f);
    notifyObserver(e);
}

void CgQtGui::slotLayers(int value){
    float f = static_cast<float>(value);
    CgBaseEvent* e = new CgSpinboxEvent(Cg::CgSpinboxEvent, f);
    notifyObserver(e);
}

void CgQtGui::slotShowNormals(){

    CgBaseEvent* e = new CgCheckBoxEvent(Cg::CgCheckBoxEvent);
    notifyObserver(e);
}

void CgQtGui::slotButtonGroupSelectionChanged()
{

}

void CgQtGui::slotMySpinBox1Changed()
{

}

void CgQtGui::slotMyCheckBox1Changed()
{

}


void CgQtGui::slotLoadMeshFile()
{
    std::cout << "load Mesh file callback reached, but not implemented..." << std::endl;
    // Hier FileChooser öffnen, datei selektieren
    // und dann neuen Event implementieren, der das an den Controller schickt.
    // dort wird dann die Datei tatsächliche geöffnet und ein entsprechendes Mesh Objekt angelegt
    // im View(GUI) passiert nichts außer festellung DASS geladen werden soll und welche Datei und zu welchem Zweck (Mesh)
}

void CgQtGui::slotMyButton1Pressed()
{
   std::cout << "button 1 pressed " << std::endl;

}


void CgQtGui::mouseEvent(QMouseEvent* event)
{

   // std::cout << QApplication::keyboardModifiers() << std::endl;

  //  if(QApplication::keyboardModifiers().testFlag(Qt::ControlModifier)==true)
    //    std::cout << Cg::ControlModifier << endl;


   if(event->type()==QEvent::MouseButtonPress)
   {


        CgBaseEvent* e = new CgMouseEvent(Cg::CgMouseButtonPress,
                                          glm::vec2(event->localPos().x() ,event->localPos().y()),
                                          (Cg::MouseButtons)event->button());

        notifyObserver(e);
   }

   if(event->type()==QEvent::MouseMove)
   {
       CgBaseEvent* e= new CgMouseEvent(Cg::CgMouseMove,
                                        glm::vec2(event->localPos().x() ,event->localPos().y()),
                                        (Cg::MouseButtons)event->button());
       notifyObserver(e);
   }



}

void CgQtGui::keyPressEvent(QKeyEvent *event)
{
   CgBaseEvent* e= new CgKeyEvent(Cg::CgKeyPressEvent,(Cg::Key)event->key(),(Cg::KeyboardModifiers)event->nativeModifiers(),event->text().toStdString());
   notifyObserver(e);
}
/*
//colorEvent
void CgQtGui::colorEvent(QPaintEvent* event){

}
*/


void CgQtGui::viewportChanged(int w, int h)
{
     CgBaseEvent* e = new CgWindowResizeEvent(Cg::WindowResizeEvent,w,h);
     notifyObserver(e);
}


CgBaseRenderer* CgQtGui::getRenderer()
{
    return m_glRenderWidget;
}





