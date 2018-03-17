#ifndef INVKINTEST_H
#define INVKINTEST_H

#ifdef __linux__
#include <GL/gl.h>
#endif
#ifdef __APPLE__
#include <OpenGL/gl.h>
#endif

#include <cmath>
#include "glm/glm.hpp"
#include "glm/gtc/random.hpp"
#include <vector>


class InvKinTest
{
public:
    InvKinTest();
    ~InvKinTest();
    void MakeArms(glm::vec3 m_origin, int m_numArms);
    void drawArms();
    void rotateArms(int i, float angle);
    void update();
    void solveIk(glm::vec3 m_goal);
    void solveIkwhole(glm::vec3 m_goal);

    void solveIkstep(glm::vec3 m_goal);

    struct Arm{
        glm::vec3 m_p1;
        glm::vec3 m_p2;
        glm::vec3 m_rot = glm::vec3(0,0,1);

        glm::vec3 m_p2prime;
        glm::vec3 m_p1prime;
        float m_len = 10.0;
        float m_angle=0;
    };
    //glm::vec3 goal = glm::vec3(0,0,3);
    std::vector<Arm> ArmList;
    std::vector<glm::vec3> VertArray;

};

#endif // INVKINTEST_H
