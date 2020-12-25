package com.luowei.opengles

import android.content.Context
import android.graphics.BitmapFactory
import android.opengl.GLSurfaceView
import android.util.AttributeSet
import android.util.Log
import android.view.MotionEvent
import java.nio.ByteBuffer

class MyGLSurfaceView : GLSurfaceView {
    constructor(context: Context?) : super(context)
    constructor(context: Context?, attrs: AttributeSet?) : super(context, attrs)


    private var totalDx: Float = 0f
    private var totalDy: Float = 0f
    private var downY: Float = 0f
    private var downX: Float = 0f
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

    fun showBitmap() {
        val bitmap = BitmapFactory.decodeStream(context.assets.open("container.png"))
        val bytes = bitmap.byteCount
        val buf = ByteBuffer.allocate(bytes)
        bitmap.copyPixelsToBuffer(buf)
        val byteArray = buf.array()
        renderer.showBitmap(bitmap.width, bitmap.height, byteArray)
    }

    override fun onTouchEvent(event: MotionEvent): Boolean {
        when (event.actionMasked) {
            MotionEvent.ACTION_DOWN -> {
                downX = event.x
                downY = event.y
            }
            MotionEvent.ACTION_MOVE -> {
                val dx = (event.x - downX) / 1000
                val dy = (event.y - downY) / 1000
                Log.d(TAG, "onTouchEvent: $dx, $dy")
                renderer.native_touch(totalDx+dx, totalDy+dy)
            }
            MotionEvent.ACTION_UP -> {
                val dx = (event.x - downX) / 1000
                val dy = (event.y - downY) / 1000
                totalDx += dx
                totalDy += dy
            }
        }
        return true
    }

    companion object {
        private const val TAG = "MyGLSurfaceView"
    }

}