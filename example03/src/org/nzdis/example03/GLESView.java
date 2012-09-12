package org.nzdis.example03;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.Log;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * Simple demo for drawing a terrain.
 * 
 * @author mariusz
 */
public class GLESView extends GLSurfaceView {
	private ExampleRenderer renderer;

	public GLESView(Context context) {
		super(context);
		Log.i("TERRAIN Example", "*********** GLESView()");
		setEGLContextClientVersion(2);
		renderer = new ExampleRenderer();
		setRenderer(renderer);
	}

	public void onPause() {
		GLESView.myCleanup();
		super.onPause();
	}

	public static native void myCleanup();
	public static native void myStartSensors();
	public static native void myDrawFrame();
	public static native void mySurfaceChanged(int width, int height);
	public static native void mySurfaceCreated();
	
	
	
	private static class ExampleRenderer implements GLSurfaceView.Renderer {

		@Override
		public void onDrawFrame(GL10 unused) {
			myDrawFrame();
		}

		@Override
		public void onSurfaceChanged(GL10 unused, int width, int height) {
			Log.i("TERRAIN Example", "*********** GLESView.onSurfaceChanged()");
			mySurfaceChanged(width, height);
		}

		@Override
		public void onSurfaceCreated(GL10 unused, EGLConfig config) {
			Log.i("TERRAIN Example", "*********** GLESView.onSurfaceCreated()");
			mySurfaceCreated();
		}
	}
	
	static {
		System.loadLibrary("simple");
	}

}