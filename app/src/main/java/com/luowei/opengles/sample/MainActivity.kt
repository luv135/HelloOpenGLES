package com.luowei.opengles.sample

import android.opengl.GLES20
import android.os.Bundle
import android.widget.ImageView
import androidx.appcompat.app.AppCompatActivity
import com.luowei.opengles.MyRenderer
import java.nio.IntBuffer

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        val imageView = findViewById<ImageView>(R.id.image_view)
        val myRenderer = MyRenderer()
        myRenderer.native_SurfaceCreated()
        myRenderer.native_onDrawFrame()
        imageView.setImageBitmap(Utils.createBitmapFromGLSurface(0, 0, 500, 500));

        // Example of a call to a native method
//        findViewById<TextView>(R.id.sample_text).text = stringFromJNI()
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    companion object {
        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("native-render")
        }
    }
}