#include <jni.h>
#include <string>
#include <GLES3/gl3.h>
#include "LogUtil.h"
#include "Triangle.h"


Triangle *triangle = NULL;

extern "C" JNIEXPORT jstring JNICALL
Java_com_luowei_opengles_sample_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}extern "C"
JNIEXPORT void JNICALL
Java_com_luowei_opengles_MyRenderer_native_1SurfaceCreated(JNIEnv *env, jobject thiz) {
    if (triangle == NULL) {
        triangle = new Triangle();
    }
    triangle->Init();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_luowei_opengles_MyRenderer_native_1onDrawFrame(JNIEnv *env, jobject thiz) {
    triangle->Draw();
}extern "C"
JNIEXPORT void JNICALL
Java_com_luowei_opengles_MyRenderer_native_1SurfaceChanged(JNIEnv *env, jobject thiz, jint width,
                                                           jint height) {
    glViewport(0, 0, width, height);
    triangle->SurfaceChanged(width,height);
}