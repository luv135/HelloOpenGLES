//
// Created by lu0we on 2020/12/15.
//

#ifndef HELLOOPENGLES_TRIANGLE_H
#define HELLOOPENGLES_TRIANGLE_H


#include <GLES3/gl3.h>
#include <sys/types.h>
#include "../util/ImageDef.h"

class Triangle {
public:
    Triangle();

    ~Triangle();

    int Init();

    int Draw() const;

    GLuint shaderProgram;
    unsigned int VAO;
    unsigned int VBO;
    GLuint textureId;
    NativeImage m_RenderImage;
    void SurfaceChanged(int width, int height) const;

    void LoadImage(NativeImage *pImage);
};


#endif //HELLOOPENGLES_TRIANGLE_H
