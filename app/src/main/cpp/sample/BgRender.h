//
// Created by lu0we on 2020/12/21.
//

#ifndef HELLOOPENGLES_BGRENDER_H
#define HELLOOPENGLES_BGRENDER_H


#include <EGL/egl.h>
#include <GLES3/gl3.h>
class BgRender {

public:
    int CreateGlesEnv();
    int Init();
    EGLDisplay m_eglDisplay;
    EGLConfig  m_eglConf;

    EGLSurface m_eglSurface;
    EGLContext m_eglCtx;

    int Draw();

    GLuint shaderProgram;
    GLuint VAO;
};


#endif //HELLOOPENGLES_BGRENDER_H
