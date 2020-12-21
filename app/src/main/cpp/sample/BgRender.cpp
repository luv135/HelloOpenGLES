//
// Created by lu0we on 2020/12/21.
//

#include "BgRender.h"
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include "../util/GLUtils.h"

int BgRender::CreateGlesEnv() {
    const EGLint confAttr[] = {
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT_KHR,
            EGL_SURFACE_TYPE,
            EGL_PBUFFER_BIT,//EGL_WINDOW_BIT EGL_PBUFFER_BIT we will create a pixelbuffer surface
            EGL_RED_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_BLUE_SIZE, 8,
            EGL_ALPHA_SIZE, 8,// if you need the alpha channel
            EGL_DEPTH_SIZE, 8,// if you need the depth buffer
            EGL_STENCIL_SIZE, 8,
            EGL_NONE
    };

    const EGLint ctxAttr[] = {
            EGL_CONTEXT_CLIENT_VERSION, 2,
            EGL_NONE
    };

    const EGLint surfaceAttr[] = {
            EGL_WIDTH, 500,
            EGL_HEIGHT, 500,
            EGL_NONE
    };

    EGLint eglMajVers, eglMinVers;
    EGLint numbConfigs;

    int resultCode = 0;
    // 获取 EGLDisplay 对象, 建立与本地窗口系统的连接
    m_eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    // 初始化 EGL
    eglInitialize(m_eglDisplay, &eglMajVers, &eglMinVers);
    // 获取 EGLConfig 对象, 确定渲染表面的配置信息
    eglChooseConfig(m_eglDisplay, confAttr, &m_eglConf, 1, &numbConfigs);

    // 创建渲染表面 EGLSurface, 此次使用屏外渲染
    m_eglSurface = eglCreatePbufferSurface(m_eglDisplay, m_eglConf, surfaceAttr);
    // 创建上下文
    m_eglCtx = eglCreateContext(m_eglDisplay, m_eglConf, EGL_NO_CONTEXT, ctxAttr);
    // 绑定上下文
    eglMakeCurrent(m_eglDisplay, m_eglSurface, m_eglSurface, m_eglCtx);

    return 0;
}


int BgRender::Draw() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    return 0;
}

const char *vertexShaderSource = "#version 300 es\n"
                                 "layout(location=0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "  gl_Position = vec4(aPos, 1.0);\n"
                                 "}\n";

const char *fragmentShaderSource = "#version 300 es\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "    FragColor = vec4(1.0,0.5,0.5,1.0);\n"
                                   "}\n";

const float vertices[] = {
        -0.5f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f
};

const unsigned int indices[] = {
        0, 1, 2
};

int BgRender::Init() {
    GLuint vertexShader, fragmentShader;
    shaderProgram = GLUtils::CreateProgram(vertexShaderSource, fragmentShaderSource, vertexShader,fragmentShader);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(GL_NONE);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_NONE);
    glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);

    return 0;
}
