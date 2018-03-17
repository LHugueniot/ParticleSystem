#ifndef PARTICLE_H
#define PARTICLE_H
#ifdef __linux__
    #include <GL/gl.h>
#endif
#ifdef __APPLE__
    #include <OpenGL/gl.h>
#endif

#include <cmath>
#include "glm/glm.hpp"
#include "glm/gtc/random.hpp"



class Particle
{
public:
    Particle(glm::vec3 _pos, int _type, int _life);
    void draw();
    void update();
//    int life;
    bool alive;
    glm::vec3 vel2;
    glm::vec3 vel3;
    glm::vec3 ballrand;
    enum type{firework,fire};
    //glm::vec3 firework;
private:
    int life;
    int type;
    glm::vec3 pos;
    glm::vec3 velocity;
    glm::vec4 col;
};


#endif // PARTICLE_H
