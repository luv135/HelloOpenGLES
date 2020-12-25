//
// Created by lu0we on 2020/12/15.
//

#include "Triangle.h"
#include <GLES3/gl3.h>
#include "../util/LogUtil.h"
#include "../glm/glm.hpp"
#include "../glm/gtx/transform.hpp"
#include "../glm/ext.hpp"
#include "../util/GLUtils.h"

Triangle::Triangle() {
    model = glm::mat4(1.0f);
}

Triangle::~Triangle() {
    NativeImageUtil::FreeNativeImage(&m_RenderImage);
}


int Triangle::Init() {
//    const GLubyte *version = glGetString(GL_VERSION);
//    LOGCATD("version=%s", version);
//    FboCreate();

    const char *vertexShaderSource = "#version 300 es\n"
                                     "layout(location=0) in vec3 aPos;\n"
                                     "layout(location=1) in  vec2 aTextureCoord;\n"
                                     "out vec2 TexCoord;\n"
                                     "uniform mat4 model;\n"
                                     "uniform mat4 view;\n"
                                     "uniform mat4 projection;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
                                     //                                                                          "   gl_Position =  vec4(aPos, 1.0);\n"
                                     "    TexCoord = aTextureCoord;\n"
                                     "}\n";

    const char *fragmentShaderSource = "#version 300 es\n"
                                       "out vec4 FragColor;\n"
                                       "in vec2 TexCoord;\n"
                                       "uniform sampler2D texture1;"
                                       "void main()\n"
                                       "{\n"
                                       //                                       "   gl_FragColor = vec4(1.0, 1.0, 0.2, 1.0);\n"
                                       "   FragColor = texture(texture1, TexCoord);\n"
                                       "}\n";


//    GLuint vertexShader, fragmentShader;
    shaderProgram = GLUtils::CreateProgram(vertexShaderSource, fragmentShaderSource);
    float vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    unsigned int indices[] = {
//            0, 2, 1,
//            0, 2, 3,

            3, 6, 2,
            3, 6, 7,



//            3, 2, 6,
//            6, 3, 7,
//
//            7, 6, 5,
//            5, 7, 4,
//
//            4, 5, 0,
//            0, 5, 1,
//
//            1, 5, 6,
//            1, 2, 6,
//
//            0, 3, 7,
//            0, 7, 4
    };
//    启动测度测试
    glEnable(GL_DEPTH_TEST);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glGenBuffers(1, &VBO);
    // 绑定到 GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //复制顶点到缓冲区
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 设置如何解析顶点数据
    // 参数0为 location=0 设置的位置
    GLint aPosLocation = glGetAttribLocation(shaderProgram, "aPos");
    glVertexAttribPointer(aPosLocation, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
    glEnableVertexAttribArray(aPosLocation);

    GLint textCoordLocation = glGetAttribLocation(shaderProgram, "aTextureCoord");
    glVertexAttribPointer(textCoordLocation, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(textCoordLocation);

    glBindVertexArray(GL_NONE);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_NONE);
    glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);

    //------------------------------------
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    //设置纹理 S 轴（横轴）的拉伸方式为截取
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//设置纹理 T 轴（纵轴）的拉伸方式为截取
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

//设置纹理采样方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_RenderImage.width, m_RenderImage.height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 m_RenderImage.ppPlane[0]);

    glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
    glBindTexture(GL_TEXTURE_2D, GL_NONE);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    return 0;
}

void uniformMatrix4F(int program, const char *name, glm::mat4 mat4) {
    glUseProgram(program);
    int location = glGetUniformLocation(program, name);
    //std::cout << "location = " << location << std::endl;
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat4));
}

int Triangle::Draw() const {
//    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//    glViewport(0, 0, m_RenderImage.width, m_RenderImage.height);
//    glBindFramebuffer(GL_FRAMEBUFFER, m_FboId);
//    // fbo off screen rendering
//    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//    glClear(GL_COLOR_BUFFER_BIT);
//    glUseProgram(m_FboProgram);
//    glBindVertexArray(FBO_VAO);
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, textureId);
//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void *) 0);
//    glBindVertexArray(0);
//    glBindTexture(GL_TEXTURE_2D, 0);
//    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // 普通渲染
    glViewport(0, 0, screenW, screenH);
    glClearColor(0.2f, .3f, .3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    uniformMatrix4F(shaderProgram, "model", model);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glDrawArrays(GL_TRIANGLES, 0, 36);
//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void *) 0);
    return 0;
}


void Triangle::SurfaceChanged(int width, int height) {
    screenW = width;
    screenH = height;
    //模型矩阵
    glm::mat4 model = glm::mat4(1.0f);
    // Model matrix
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
//    model = glm::rotate(model, radiansX, glm::vec3(1.0f, 0.0f, 0.0f));
//    model = glm::rotate(model, radiansY, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    // x轴旋转
//    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    // 观察矩阵
//    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 view = glm::lookAt(
            glm::vec3(0, 0, 4), // Camera is at (0,0,1), in World Space
            glm::vec3(0, 0, 0), // and looks at the origin
            glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
    );
    float rate = (float) width / (float) height;
    LOGCATD("width = %d, height = %d, rate = %f", width, height, rate);
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), rate, 0.1f, 100.0f);

    uniformMatrix4F(shaderProgram, "model", model);
    uniformMatrix4F(shaderProgram, "view", view);
    uniformMatrix4F(shaderProgram, "projection", projection);
}

void Triangle::LoadImage(NativeImage *pImage) {
    if (pImage) {
        m_RenderImage.width = pImage->width;
        m_RenderImage.height = pImage->height;
        m_RenderImage.format = pImage->format;
        NativeImageUtil::CopyNativeImage(pImage, &m_RenderImage);
    }
}

int Triangle::FboCreate() {


    const char *vertexShaderSource = "#version 300 es\n"
                                     "layout(location=0) in vec3 aPos;\n"
                                     "layout(location=1) in  vec2 aTextureCoord;\n"
                                     "out vec2 TexCoord;\n"
                                     "uniform mat4 model;\n"
                                     "uniform mat4 view;\n"
                                     "uniform mat4 projection;\n"
                                     "void main()\n"
                                     "{\n"
                                     //                                     "   gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
                                     "   gl_Position =  vec4(aPos, 1.0);\n"
                                     "    TexCoord = aTextureCoord;\n"
                                     "}\n";

    const char *fragmentShaderSource = "#version 300 es\n"
                                       "out vec4 FragColor;\n"
                                       "in vec2 TexCoord;\n"
                                       "uniform sampler2D texture1;"
                                       "void main()\n"
                                       "{\n"
                                       //                                       "   gl_FragColor = vec4(1.0, 0.0, 0.2, 1.0);\n"
                                       "   FragColor = texture(texture1, TexCoord);\n"
                                       "}\n";


    float vertices[] = {
            //顶点坐标--------纹理坐标
            -0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
    };

    unsigned int indices[] = {
            0, 1, 2,
            2, 0, 3
    };

    m_FboProgram = GLUtils::CreateProgram(vertexShaderSource, fragmentShaderSource);
    glGenVertexArrays(1, &FBO_VAO);
    glBindVertexArray(FBO_VAO);

    glGenBuffers(1, &FBO_EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, FBO_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glGenBuffers(1, &FBO_VBO);
    // 绑定到 GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, FBO_VBO);
    //复制顶点到缓冲区
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 设置如何解析顶点数据
    // 参数0为 location=0 设置的位置
    GLint aPosLocation = glGetAttribLocation(m_FboProgram, "aPos");
    glVertexAttribPointer(aPosLocation, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
    glEnableVertexAttribArray(aPosLocation);

    GLint textCoordLocation = glGetAttribLocation(m_FboProgram, "aTextureCoord");
    glVertexAttribPointer(textCoordLocation, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(textCoordLocation);

    glBindVertexArray(GL_NONE);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_NONE);
    glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);

    //------------------------------------

    glUniform1i(glGetUniformLocation(m_FboProgram, "texture1"), 0);
    glBindTexture(GL_TEXTURE_2D, GL_NONE);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    //------------------------------------

    // 创建 2D 纹理
    glGenTextures(1, &m_FboTexutreId);
    glBindTexture(GL_TEXTURE_2D, m_FboTexutreId);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, GL_NONE);

    // 创建 FBO
    glGenFramebuffers(1, &m_FboId);
    glBindFramebuffer(GL_FRAMEBUFFER, m_FboId);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // 绑定 FBO 纹理
    glBindTexture(GL_TEXTURE_2D, m_FboTexutreId);
    // 将纹理连接到 FBO 附着
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_FboTexutreId, 0);
// 分配内存大小
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_RenderImage.width, m_RenderImage.height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, nullptr);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        LOGCATE("FBOSample::CreateFrameBufferObj glCheckFramebufferStatus status != GL_FRAMEBUFFER_COMPLETE");
        return false;
    }
    glBindTexture(GL_TEXTURE_2D, GL_NONE);
    return 0;
}

void Triangle::touch(float dx, float dy) {
    model = glm::mat4(1.0f);
    model = glm::rotate(model, dy, glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, dx, glm::vec3(0.0f, 1.0f, 0.0f));

}
