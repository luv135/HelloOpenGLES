package com.luowei.opengles

import android.opengl.GLSurfaceView
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class MyRenderer : GLSurfaceView.Renderer {
    override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
        native_SurfaceCreated()
    }

    external fun native_SurfaceCreated()
    external fun native_SurfaceChanged(width: Int, height: Int)
    external fun native_onDrawFrame()

    override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
        native_SurfaceChanged(width,height)
    }

    override fun onDrawFrame(gl: GL10?) {
        native_onDrawFrame()
    }
}