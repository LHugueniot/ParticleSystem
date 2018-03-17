#include "InvKinTest.h"
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif
#define GLM_SWIZZLE
#include "glm/glm.hpp"
#include <iostream>
#include <cstdlib>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtx/transform.hpp>

InvKinTest::InvKinTest()
{

}

InvKinTest::~InvKinTest()
{

}

void InvKinTest::MakeArms(glm::vec3 m_origin, int m_numArms)
{
    glm::vec3 temp;
    auto numArms=m_numArms;
    for(int i=0; i<numArms;i++)
    {
        Arm p;
        if(i==0)
        {
            ArmList.push_back(p);
            ArmList[i].m_p1=m_origin;
            ArmList[i].m_p2=ArmList[i].m_p1+glm::vec3(1,0,0)*ArmList[i].m_len;
        }
        else
        {
            ArmList.push_back(p);
            ArmList[i].m_p1=ArmList[i-1].m_p2;
            ArmList[i].m_p2=ArmList[i].m_p1+glm::vec3(1,0,0)*ArmList[i].m_len;
        }
    }
}

void InvKinTest::update()
{
    for(int i=1; i<ArmList.size();i++)
    {
    }


}

//void InvKinTest::Smooth(glm::vec3 m_goal,int time)
//{
//    auto diffVec=m_goal- ArmList[i].m_p2;
//    auto distVec=glm::length(diffVec);
//    auto step = distVec/time;
//    auto stepgoal=diffVec;


//    //for()
//    solveIk(stepgoal);
//}

void InvKinTest::solveIk(glm::vec3 m_goal)
{
    auto goal=m_goal;
    auto maxLength=glm::length(goal-ArmList[0].m_p1);
    bool solved=false;
    if(maxLength<ArmList.size()*10)
    {
        if(!solved)
        {
            for(int i=ArmList.size(); i>0;i--)
            {
                if(i==ArmList.size())
                {
                    ArmList[i].m_p2prime=goal;
                    ArmList[i].m_p1prime=glm::normalize(ArmList[i].m_p1-ArmList[i].m_p2prime)*ArmList[i].m_len+ArmList[i].m_p2prime;

                    auto distance= glm::length(goal - ArmList[ArmList.size()].m_p2);
                    //printf("%d\n",i);
                    //printf("%f\n",ArmList[i].m_p1prime);
                }
                else
                {
                    ArmList[i].m_p2prime=ArmList[i+1].m_p1prime;
                    ArmList[i].m_p1prime=glm::normalize(ArmList[i].m_p1-ArmList[i].m_p2prime)*ArmList[i].m_len+ArmList[i].m_p2prime;

                    auto distance= glm::length(goal - ArmList[ArmList.size()].m_p2);
                    printf("%f\n",distance);
                }

                printf("%d\n",i);
            }
            for(int i=0; i<ArmList.size();i++)
            {
                if(i==ArmList.size())
                {
                    ArmList[i].m_p2=glm::normalize(ArmList[i].m_p2prime-ArmList[i].m_p1)*ArmList[i].m_len+ArmList[i].m_p1;

                    auto distance= glm::length(goal - ArmList[ArmList.size()].m_p2);
                    printf("%f\n",distance);

                }
                else
                {
                    ArmList[i].m_p2=glm::normalize(ArmList[i].m_p2prime-ArmList[i].m_p1)*ArmList[i].m_len+ArmList[i].m_p1;
                    ArmList[i+1].m_p1=ArmList[i].m_p2;

                    auto distance= glm::length(goal - ArmList[ArmList.size()].m_p2);
                    printf("%f\n",distance);
                }
            }
            auto distance= glm::length(goal - ArmList[ArmList.size()].m_p2);
            if(distance<0.2)
            {
                solved=true;
            }
        }
    }
    else
    {
        goal=glm::normalize(goal)*maxLength;
        for(int i=0; i<ArmList.size();i++)
        {
            //ArmList[i].m_p1
        }

    }
}

void InvKinTest::drawArms()
{
    for(int i=0; i<ArmList.size();i++)
    {

        glm::vec3 p1=ArmList[i].m_p1;
        glm::vec3 p2=ArmList[i].m_p2;
        //printf("hi \np1=%f%f%f \np2=%f%f%f",p1.x,p1.y,p1.z,p2.x,p2.y,p2.z);
        glLineWidth(1);
        glColor3f(1,0,0);

        glBegin(GL_POINTS);
        glPointSize(100);
        glVertex3f(p1.x,p1.y,p1.z);
        glVertex3f(p2.x,p2.y,p2.z);
        glEnd();

        glBegin(GL_LINES);
        glVertex3f(p1.x,p1.y,p1.z);
        glVertex3f(p2.x,p2.y,p2.z);
        glEnd();
        //printf("\n\n");
    }
}

void InvKinTest::rotateArms(int i, float angle)
{

    ArmList[i].m_angle=angle;//*ArmList[i].m_len;
    update();
}

//-----------------------------#shitcode--------------------------------------

void InvKinTest::solveIkwhole(glm::vec3 m_goal)
{
    bool running=true;
    bool can=true;
    if (can)
    {
        solveIk(m_goal);
        drawArms();
        auto goal=m_goal;
        float distance= glm::length(goal - ArmList[ArmList.size()].m_p2);
        if (distance < 0.2)running = false;
    }
}


void InvKinTest::solveIkstep(glm::vec3 m_goal)
{
    auto goal=m_goal;
    auto maxLength=glm::length(goal-ArmList[0].m_p1);
    bool solved=false;

    for(int i=ArmList.size(); i>0;i--)
    {
        if(i==ArmList.size())
        {
            ArmList[i].m_p2prime=goal;
            ArmList[i].m_p1prime=glm::normalize(ArmList[i].m_p1-ArmList[i].m_p2prime)*ArmList[i].m_len+ArmList[i].m_p2prime;

            auto distance= glm::length(goal - ArmList[ArmList.size()].m_p2);
            //printf("%d\n",i);
            //printf("%f\n",ArmList[i].m_p1prime);
        }
        else
        {
            ArmList[i].m_p2prime=ArmList[i+1].m_p1prime;
            ArmList[i].m_p1prime=glm::normalize(ArmList[i].m_p1-ArmList[i].m_p2prime)*ArmList[i].m_len+ArmList[i].m_p2prime;

            auto distance= glm::length(goal - ArmList[ArmList.size()].m_p2);
            printf("%f\n",distance);
        }

        printf("%d\n",i);
    }
    for(int i=0; i<ArmList.size();i++)
    {
        if(i==ArmList.size())
        {
            ArmList[i].m_p2=glm::normalize(ArmList[i].m_p2prime-ArmList[i].m_p1)*ArmList[i].m_len+ArmList[i].m_p1;

            auto distance= glm::length(goal - ArmList[ArmList.size()].m_p2);
            printf("%f\n",distance);

        }
        else
        {
            ArmList[i].m_p2=glm::normalize(ArmList[i].m_p2prime-ArmList[i].m_p1)*ArmList[i].m_len+ArmList[i].m_p1;
            ArmList[i+1].m_p1=ArmList[i].m_p2;

            auto distance= glm::length(goal - ArmList[ArmList.size()].m_p2);
            printf("%f\n",distance);
        }
    }
    auto distance= glm::length(goal - ArmList[ArmList.size()].m_p2);

}
