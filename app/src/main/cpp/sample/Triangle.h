//
// Created by lu0we on 2020/12/15.
//

#ifndef HELLOOPENGLES_TRIANGLE_H
#define HELLOOPENGLES_TRIANGLE_H


#include <GLES3/gl3.h>
#include <sys/types.h>
#include "../util/ImageDef.h"
#include "../glm/glm.hpp"

class Triangle {
public:
    Triangle();

    ~Triangle();

    int Init();

    int Draw() const;

    int FboCreate();


    GLuint shaderProgram;
    unsigned int VAO;
    unsigned int VBO;
//    unsigned int EBO;
    GLuint textureId;
    NativeImage m_RenderImage;
    void SurfaceChanged(int width, int height) ;

    void LoadImage(NativeImage *pImage);

    GLuint m_FboTexutreId;
    GLuint m_FboId;
    GLuint m_FboProgram;
    GLuint FBO_VAO;
    GLuint FBO_EBO;
    GLuint FBO_VBO;


    int screenW;
    int screenH;
    glm::mat4 model;
    glm::mat4 view;;
    void touch(float dx, float dy);
};


#endif //HELLOOPENGLES_TRIANGLE_H
