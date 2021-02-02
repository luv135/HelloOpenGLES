//
// Created by lu0we on 2020/12/28.
//

#include "Light.h"
#include <GLES3/gl3.h>

int Light::Init() {
    const char *vertexShaderSource =  "#version 300 es\n"
    "layout (location = 0) in vec3 position;\n"
    "\n"
    "uniform mat4 model;\n"
    "uniform mat4 view;\n"
    "uniform mat4 projection;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    gl_Position = projection * view * model * vec4(position, 1.0f);\n"
    "}";
    GLuint lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);


    return 0;
}
