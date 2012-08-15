package org.nzdis;

import android.app.Activity;
import android.os.Bundle;
import android.content.pm.ActivityInfo;
import android.opengl.GLSurfaceView;
import android.view.Window;
import android.view.WindowManager;

/**
 * Simple example demonstrating OpenGL surface view.
 * 
 * @author mariusz
 */
public class Example01 extends Activity {

	private ExampleView surfaceView;
    
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        requestWindowFeature(Window.FEATURE_NO_TITLE);
    	setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
    	getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);

    	surfaceView = new ExampleView(this);
    	setContentView(surfaceView);
    }

  	@Override
  	protected void onResume() {
    	super.onResume();
    	surfaceView.onResume();
  	}

	@Override
  	protected void onPause() {
    	super.onPause();
    	surfaceView.onPause();
  	}

}
