package org.nzdis.example03;

import android.content.Context;
import android.opengl.GLSurfaceView;
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
  	setEGLContextClientVersion(2);
    renderer = new ExampleRenderer();
    setRenderer(renderer);
  }

	static {
		System.loadLibrary("simple");
	}
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
    	mySurfaceChanged(width, height);
    }

    @Override
    public void onSurfaceCreated(GL10 unused, EGLConfig config) {
    	mySurfaceCreated();
    }
  }
}