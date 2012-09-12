package org.nzdis.example03;

import android.os.Bundle;
import android.os.PowerManager;
import android.app.Activity;
import android.content.Context;
import android.content.pm.ActivityInfo;
import android.util.Log;
import android.view.Window;
import android.view.WindowManager;

public class TerrainExample extends Activity {


	private GLESView surfaceView;
	
	private PowerManager.WakeLock wl = null;
    
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Log.i("TERRAIN Example", "*********** TerrainExample.onCreate()");
        requestWindowFeature(Window.FEATURE_NO_TITLE);
    	setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
    	getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);

    	surfaceView = new GLESView(this);
    	setContentView(surfaceView);
    	
    	PowerManager pm = (PowerManager) getSystemService(Context.POWER_SERVICE);
    	wl = pm.newWakeLock(PowerManager.SCREEN_BRIGHT_WAKE_LOCK, "TerrainExample");
    }

  	@Override
  	protected void onResume() {
    	super.onResume();
    	Log.i("TERRAIN Example", "*********** TerrainExample.onResume()");
    	wl.acquire();
    	surfaceView.onResume();
    	new Thread(new Runnable() {
    		public void run() {
    			GLESView.myStartSensors();
    		}
    	}).start();
  	}

	  @Override
  	protected void onPause() {
    	super.onPause();
    	Log.i("TERRAIN Example", "*********** TerrainExample.onPause()");
    	wl.release();
    	surfaceView.onPause();
  	}
	
}
