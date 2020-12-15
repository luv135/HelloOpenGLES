//
// Created by lu0we on 2020/12/15.
//

#ifndef HELLOOPENGLES_TRIANGLE_H
#define HELLOOPENGLES_TRIANGLE_H


#include <GLES3/gl3.h>

class Triangle {
public:
    Triangle();

    ~Triangle();

    int Init();

    int Draw();

    GLuint shaderProgram;
    unsigned int VAO;
    unsigned int VBO;

};


#endif //HELLOOPENGLES_TRIANGLE_H
