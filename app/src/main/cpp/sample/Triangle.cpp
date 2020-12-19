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
}

Triangle::~Triangle() {
    NativeImageUtil::FreeNativeImage(&m_RenderImage);
}

int Triangle::Init() {
//    const GLubyte *version = glGetString(GL_VERSION);
//    LOGCATD("version=%s", version);

    const char *vertexShaderSource = "#version 100\n"
                                     "attribute vec3 aPos;\n"
                                     "varying vec2 TexCoord;\n"
                                     "attribute vec2 aTextureCoord;\n"
                                     "uniform mat4 model;\n"
                                     "uniform mat4 view;\n"
                                     "uniform mat4 projection;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
                                     //                                     "   gl_Position =  vec4(aPos, 1.0);\n"
                                     "    TexCoord = aTextureCoord;\n"
                                     "}\n";

    const char *fragmentShaderSource = "#version 100\n"
                                       "precision mediump float;\n"
                                       "varying vec2 TexCoord;\n"
                                       "uniform sampler2D texture1;"
                                       "void main()\n"
                                       "{\n"
                                       //                                       "   gl_FragColor = vec4(1.0, 1.0, 0.2, 1.0);\n"
                                       "   gl_FragColor = texture2D(texture1, TexCoord);\n"
                                       "}\n";


    GLuint vertexShader, fragmentShader;
    shaderProgram = GLUtils::CreateProgram(vertexShaderSource, fragmentShaderSource, vertexShader,
                                           fragmentShader);





//    // 创建顶点着色器
//    vertexShader = glCreateShader(GL_VERTEX_SHADER);
//    // 关联源码
//    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//    // 编译
//    glCompileShader(vertexShader);
//
//    int success;
//    char infoLog[512];
//    // 检查编译结果
//    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//    if (!success) {
//        // 输出日志信息
//        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//        LOGCATE("vertex shader error %s", infoLog);
//        return -1;
//    }
//    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//    glCompileShader(fragmentShader);
//    // 检查编译结果
//    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//    if (!success) {
//        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
//        LOGCATE("fragmentShader ERROR %s", infoLog);
//        return -1;
//    }
    // 创建着色器程序
//    shaderProgram = glCreateProgram();
//    // 着色器附加到程序
//    glAttachShader(shaderProgram, vertexShader);
//    glAttachShader(shaderProgram, fragmentShader);
//    // 链接
//    glLinkProgram(shaderProgram);
//    // 检查编译结果
//    glGetShaderiv(shaderProgram, GL_COMPILE_STATUS, &success);
//    if (!success) {
//        glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
//        LOGCATE("glLinkProgram ERROR %s", infoLog);
//        return -1;
//    }
//    // 链接到程序后,不再需要,删除
//    glDeleteShader(vertexShader);
//    glDeleteShader(fragmentShader);


    float vertices[] = {
            //顶点坐标--------纹理坐标
            -0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 1.0f,

            0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.0f, 0.0f, 0.0f
    };

    // 创建顶点缓冲对象 vbo
    glGenBuffers(1, &VBO);
    // 顶点数组对象
    glGenVertexArrays(1, &VAO);
    // 绑定VAO
    glBindVertexArray(VAO);

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
                          (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(textCoordLocation);


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

int Triangle::Draw() const {
    glClearColor(0.2f, .3f, .3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    return 0;
}

void uniformMatrix4F(int program, const char *name, glm::mat4 mat4) {
    glUseProgram(program);
    int location = glGetUniformLocation(program, name);
    //std::cout << "location = " << location << std::endl;
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat4));
}

void Triangle::SurfaceChanged(int width, int height) const {

    //模型矩阵
    glm::mat4 model = glm::mat4(1.0f);
    // x轴旋转
//    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    // 观察矩阵
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float) (width / height), 0.1f, 100.0f);

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
