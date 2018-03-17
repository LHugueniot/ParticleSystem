#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif
#include "glm/glm.hpp"
#include "particle.h"
#include <iostream>
#include <cstdlib>
#include <glm/gtc/random.hpp>

Particle::Particle(glm::vec3 _pos, int _type, int _life)
{
    life = _life;
    type = _type;
    pos = _pos;
    velocity = glm::vec3(0,0,0);
    vel2 = glm::vec3(0,glm::diskRand(1.0f));
    vel3 = glm::sphericalRand(1.0f);
    ballrand = glm::ballRand(0.2f);
    //    col.r= ((float) rand() / (RAND_MAX));
    //    col.g= ((float) rand() / (RAND_MAX));
    //    col.b= ((float) rand() / (RAND_MAX));
    if(type==firework)
    {
        col.r= 1;
        col.g= 0.5;
        col.b= 0;
        col.a=1;
    }
    if(type==fire)
    {

        col.r= 255/255;
        col.g= 127/255;
        col.b= 80/255;
        col.a=1;
    }
    alive = true;

}

void Particle::draw()
{
    if(alive == true)
    {
        glColor4f(col.r,col.g,col.b,col.a);
        glPointSize(3);
        glBegin(GL_POINTS);
        glVertex3f(pos.x,pos.y,pos.z);
        glEnd();
        glColor4f(col.r,col.g,col.b,col.a);
        glPointSize(2);
        glBegin(GL_POINTS);
        glVertex3f(pos.x-10*velocity.x,pos.y-10*velocity.y,pos.z-10*velocity.z);
        glEnd();
        glColor4f(col.r,col.g,col.b,col.a);
        glPointSize(1);
        glBegin(GL_POINTS);
        glVertex3f(pos.x-20*velocity.x,pos.y-20*velocity.y,pos.z-20*velocity.z);
        glEnd();

    }
}

void Particle::update()
{
    //glm::vec3 ballrand = glm::ballRand(2.0f);
    if(type==firework)
    {
        if(alive == true)
        {
            pos+=velocity;

            if(life>150)
            {
                velocity= glm::vec3(0.2,0,0);;
            }
            if(life<150)
            {
                velocity=ballrand;
            }
            --life;
        }
    }
    if(type==fire)
    {
        //std::cout<<life<<'\n';

        if(alive == true)
        {
            pos+=velocity;
            velocity= glm::vec3(0.2,glm::diskRand(0.1f));
                    --life;

            while(col.g < 1.0f||col.b>0)
            {
                col.g+=0.0001;
                col.b-=0.0001;
            }
        }
    }

    if(life<=0)
    {
        alive = 0;
    }

}

