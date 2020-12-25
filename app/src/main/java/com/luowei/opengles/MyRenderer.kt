package com.luowei.opengles

import android.opengl.GLSurfaceView
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class MyRenderer : GLSurfaceView.Renderer {
    external fun native_SurfaceCreated()
    external fun native_SurfaceChanged(width: Int, height: Int)
    external fun native_onDrawFrame()
    external fun native_showBitmap(width: Int, height: Int, byteArray: ByteArray)
    external fun native_touch(dx: Float, dy: Float)

    override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
        native_SurfaceCreated()
    }

    override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
        native_SurfaceChanged(width, height)
    }

    override fun onDrawFrame(gl: GL10?) {
        native_onDrawFrame()
    }

    fun showBitmap(width: Int, height: Int, bytes: ByteArray) {
        native_showBitmap(width, height, bytes)
    }

}