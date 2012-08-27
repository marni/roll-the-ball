package org.nzdis.example03;

import android.os.Bundle;
import android.app.Activity;
import android.content.pm.ActivityInfo;
import android.view.Window;
import android.view.WindowManager;

public class TerrainExample extends Activity {


	private GLESView surfaceView;
    
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        requestWindowFeature(Window.FEATURE_NO_TITLE);
    	setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
    	getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);

    	surfaceView = new GLESView(this);
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
      GLESView.myCleanup();
  	}
	
}
