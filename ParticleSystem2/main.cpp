#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif
#include <iostream>
#include <cstdlib>
#include <glm/glm.hpp>
#include "sdlwindow.h"
#include "particle.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <algorithm>
#include "InvKinTest.h"
// constants
const int WIDTH = 720*1.5;
const int HEIGHT = 576*1.5;
// function to init the basic OpenGL scene for this demo
int framecount = 0;
std::vector<Particle>fuzzy;
std::vector<InvKinTest>waddup;
float angle=0;
int num_part=100;
int mean_fire_part_num;
int current_num_part=0;
bool fireon=false;
enum _type{firework,fire};
void initOpenGL();
// function to render our scene.
void grid();
void draw();
void spawn(int type);
void line(double _p1x,double _p1y,double _p1z,double _p2x,double _p2y,double _p2z,double _r,double _g,double _b);
void loadView();
int main()
{
    SDLWindow win("Particle System demo", 0,0, WIDTH, HEIGHT);

    InvKinTest* test=new InvKinTest;
    win.makeCurrent();
    win.setBackground();
    initOpenGL();
    bool quit=false;
    while(!quit)
    {
        SDL_Event event;
        //glm::perspective(glm::radians(180.f),6.0f,0.1f,1000.0f);

        // grab the event from the window (note this explicitly calls make current)
        win.pollEvent(event);
        switch (event.type)
        {
        // this is the window x being clicked.
        case SDL_QUIT : quit = true; break;
            // now we look for a keydown event
        case SDL_KEYDOWN:
        {
            switch( event.key.keysym.sym )
            {
            // if it's the escape key quit
            case SDLK_ESCAPE :  quit = true; break;
                // make OpenGL draw wireframe
            case SDLK_w :
                spawn(firework);
                break;
            case SDLK_a :
                fireon=!fireon;

                //std::cout << std::boolalpha << fireon << '\n';
                break;
                // make OpenGL draw solid
            case SDLK_s :
                glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
                break;
            case SDLK_LEFT :
                win.rotate.z +=1;
                break;
            case SDLK_RIGHT :
                win.rotate.z -=1;
                break;
            case SDLK_UP :
                win.rotate.x +=1;
                break;
            case SDLK_DOWN :
                win.rotate.x -=1;
                break;
            case SDLK_r :
                test->solveIkwhole(glm::vec3(0,99,0));
                //std::cout<<"%f"<<waddup[0].ArmList[0].m_angle;
                break;
            case SDLK_d :
                test->MakeArms(glm::vec3(0,0,10),10);
                test->drawArms();
                break;
            } // end of key process
        } // end of keydown

        default : break;
        } // end of event switch


        loadView();

        if(55>=win.rotate.x)
        {
            win.rotate.x=win.rotate.x+1;
        }

        if(win.rotate.x>=-125)
        {
            win.rotate.x=win.rotate.x-1;
        }
        glRotatef(win.rotate.x,0,-0.5,0.5);
        glRotatef(win.rotate.z,1,0,0);

        if(fireon==true)
        {
            spawn(fire);
        }

        for(auto &p : fuzzy)
        {
            p.draw();
            p.update();
            if (p.alive==0)
            {
                fuzzy.erase(fuzzy.begin());
            }

        }

        grid();
        test->drawArms();
        win.swapWindow();
        ++framecount;
        //std::cout<<framecount<<"\n";
        //std::cout<<fuzzy.size()<<"\n";
    }

    return EXIT_SUCCESS;

}



void initOpenGL()
{
    glClearColor(0.8,0.8,0.8,1.0);
    glEnable(GL_POINT_SMOOTH);
}


void loadView()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMultMatrixf(glm::value_ptr(glm::perspective(0.5f,float(WIDTH/HEIGHT),0.01f,500.0f)));
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMultMatrixf(glm::value_ptr(glm::lookAt(glm::vec3(250.0f, 250.0f, 250.0f),glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1.0f, 0.0f, 0.0f))));

}


void spawn(int type)
{

    int firework_life=500;
    //int fire_life=50 + ((rand() % (-1) + 1)*50);
    int fire_life=(200 + (rand() % 1 + 50));
    //std::cout<<fire_life<<'\n';
    if(type==firework)
    {
        for(int i=0;i<num_part;i++)
        {
            Particle p(glm::vec3(0,0,0),firework,firework_life);
            fuzzy.push_back(p);
        }
    }
    if(type==fire)
    {
        Particle p(glm::vec3(glm::sphericalRand(10.0f)),fire,fire_life);
        fuzzy.push_back(p);
    }
}

void grid()
{
    for(int i=-5;i<=5;i++)
    {

        line(0.0,50.0,(i*10.0),0.0,-50.0,(i*10.0),1,1,1);
        line(0.0,(i*10.0),50.0,0.0,(i*10.0),-50.0,1,1,1);
    }
    line(0,0,0,0,0,20,0,0,1); //line z
    line(0,0,0,20,0,0,1,0,0); //line x
    line(0,0,0,0,20,0,0,1,0); //line y
}

void line(double _p1x,double _p1y,double _p1z,double _p2x,double _p2y,double _p2z,double _r,double _g,double _b)
{
    double p1x=_p1x;
    double p1y=_p1y;
    double p1z=_p1z;
    double p2x=_p2x;
    double p2y=_p2y;
    double p2z=_p2z;
    glLineWidth(1);
    glColor3f(_r,_g,_b);
    glBegin(GL_LINES);
    glVertex3f(p1x,p1y,p1z);
    glVertex3f(p2x,p2y,p2z);
    glEnd();
}
