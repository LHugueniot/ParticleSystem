#ifndef SDLWINDOW_H
#define SDLWINDOW_H
#include "SDL2/SDL.h"
#include <string>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

class SDLWindow
{
public:
    SDLWindow(const std::string &_name, int _x, int _y, int _width, int _height);

    void makeCurrent() { SDL_GL_MakeCurrent(m_window, m_glContext); }
    void swapWindow() { SDL_GL_SwapWindow(m_window); }
    void setBackground();
    void pollEvent(SDL_Event &_event);
    glm::vec3 rotate = glm::vec3(1.0f,1.0f,1.0f);
    float up=4;

private:
    /// @brief width of screen
    int m_width;
    /// @brief height of screen
    int m_height;
    // xpos of window
    int m_x;
    // ypos of window
    int m_y;
    // name of window
    std::string m_name;

    void init();

    SDL_GLContext m_glContext;
    void createGLContext();

    void ErrorExit(const std::string &_msg) const;

    SDL_Window *m_window;

};
#endif // SDLWINDOW_H
