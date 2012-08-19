package org.nzdis.example02;

import android.content.Context;
import android.opengl.GLES20;
import android.opengl.GLSurfaceView;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * Simple demo and use of C-based OpenGL surface view.
 * In this example we use native calls directly to C layer, 
 * through JNI.
 * 
 * @author mariusz
 */
public class NativeGLESView extends GLSurfaceView {
  
	private ExampleRenderer renderer;

	static {
		System.loadLibrary("simple");
	}

	public static native void myDrawFrame();
	public static native void mySurfaceChanged(int width, int height);
	public static native void mySurfaceCreated();

  
	
	public NativeGLESView(Context context) {
		super(context);
		setEGLContextClientVersion(2);
		renderer = new ExampleRenderer();
		setRenderer(renderer);
	}

	
	@Override
	public void onPause() {
		super.onPause();
		// FIXME cleanup the allocated memory
	}
	
	@Override
	public void onResume() {
		super.onResume();
		// FIXME check if onSurfaceChanged or onSurfaceCreated is being called
	}
	
	
	private static class ExampleRenderer implements GLSurfaceView.Renderer {
		@Override
		public void onDrawFrame(GL10 unused) {
			myDrawFrame();
		}

		@Override
		public void onSurfaceChanged(GL10 unused, int width, int height) {
			mySurfaceChanged(width, height);
		}

		@Override
		public void onSurfaceCreated(GL10 unused, EGLConfig config) {
			mySurfaceCreated();
		}
	}
}