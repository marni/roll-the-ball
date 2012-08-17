package org.nzdis.example02;

import android.os.Bundle;
import android.app.Activity;
import android.content.pm.ActivityInfo;
import android.view.Window;
import android.view.WindowManager;

public class Example02 extends Activity {


	private NativeGLESView surfaceView;
    
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        requestWindowFeature(Window.FEATURE_NO_TITLE);
    	setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
    	getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);

    	surfaceView = new NativeGLESView(this);
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
