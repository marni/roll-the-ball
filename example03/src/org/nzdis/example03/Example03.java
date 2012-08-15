package org.nzdis.example03;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;

public class Example03 extends Activity {

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_example);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.activity_example, menu);
        return true;
    }
}
