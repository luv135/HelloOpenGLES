package com.luowei.opengles

import android.content.Context
import android.graphics.BitmapFactory
import android.opengl.GLSurfaceView
import android.util.AttributeSet
import java.nio.ByteBuffer

class MyGLSurfaceView : GLSurfaceView {
    constructor(context: Context?) : super(context)
    constructor(context: Context?, attrs: AttributeSet?) : super(context, attrs)


    private var renderer: MyRenderer

    init {

        val s =
            "#version 100\n" +
                    "uniform mat4 uMVPMatrix;\n" +
                    "uniform mat4 uTexMatrix;\n" +
                    "attribute highp vec4 aPosition;\n" +
                    "attribute highp vec4 aTextureCoord;\n" +
                    "varying highp vec2 vTextureCoord;\n" +
                    "void main() {\n" +
                    "    gl_Position = uMVPMatrix * aPosition;\n" +
                    "    vTextureCoord = (uTexMatrix * aTextureCoord).xy;\n" +
                    "}\n"
        val f = "#version 100\n" +
                "#extension GL_OES_EGL_image_external : require\n" +
                "precision mediump float;\n" +
                "uniform samplerExternalOES sTexture;\n" +
                "varying highp vec2 vTextureCoord;\n" +
                "void main() {\n" +
                "  gl_FragColor = texture2D(sTexture, vTextureCoord);\n" +
                "}"
        setEGLContextClientVersion(2)
        renderer = MyRenderer()
        setRenderer(renderer)
        showBitmap()
    }

    fun showBitmap(){
        val bitmap = BitmapFactory.decodeStream(context.assets.open("container.png"))
        val bytes = bitmap.byteCount
        val buf = ByteBuffer.allocate(bytes)
        bitmap.copyPixelsToBuffer(buf)
        val byteArray = buf.array()
        renderer.showBitmap(bitmap.width, bitmap.height, byteArray)
    }


}