#include <jni.h>
#include <string>
#include <GLES3/gl3.h>
#include "util/LogUtil.h"
#include "sample/Triangle.h"
#include "sample/BgRender.h"

//Triangle *triangle = new Triangle();
BgRender *render = new BgRender();

extern "C" JNIEXPORT jstring JNICALL
Java_com_luowei_opengles_sample_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}extern "C"
JNIEXPORT void JNICALL
Java_com_luowei_opengles_MyRenderer_native_1SurfaceCreated(JNIEnv *env, jobject thiz) {
    LOGCATD("init");
    render->CreateGlesEnv();
    render->Init();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_luowei_opengles_MyRenderer_native_1onDrawFrame(JNIEnv *env, jobject thiz) {
    render->Draw();
}extern "C"
JNIEXPORT void JNICALL
Java_com_luowei_opengles_MyRenderer_native_1SurfaceChanged(JNIEnv *env, jobject thiz, jint width,
                                                           jint height) {
    glViewport(0, 0, width, height);
//    render->SurfaceChanged(width, height);
}extern "C"
JNIEXPORT void JNICALL
Java_com_luowei_opengles_MyRenderer_native_1showBitmap(JNIEnv *env, jobject thiz, jint width,
                                                       jint height, jbyteArray imageData) {
    int len = env->GetArrayLength(imageData);
    uint8_t *buf = new uint8_t[len];
    env->GetByteArrayRegion(imageData, 0, len, reinterpret_cast<jbyte *>(buf));
    LOGCATD("MyGLRenderContext::SetImageData format=%d, width=%d, height=%d, pData=%p len=%d", IMAGE_FORMAT_RGBA,
            width, height, buf,len);
    NativeImage nativeImage;
    nativeImage.format = IMAGE_FORMAT_RGBA;
    nativeImage.width = width;
    nativeImage.height = height;
    nativeImage.ppPlane[0] = buf;
//    triangle->LoadImage(&nativeImage);
    delete[] buf;
    env->DeleteLocalRef(imageData);
}