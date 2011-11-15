package scut.attmore.shengbo.ui;

import scut.attmore.shengbo.R;
import scut.attmore.shengbo.util.ReferenceManager;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;

public class Splash extends BaseActivity {
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
       
//        ReferenceManager rm=ReferenceManager.getInstance(this);
//        rm.setFistRun(true);
        setContentView(R.layout.splash);
        new Handler().postDelayed(new Runnable() {
			@Override
			public void run() {
				Splash.this.startActivity(new Intent(Splash.this,
						MainUI.class));
				Splash.this.finish()	;
			}
		}, 2500);
    }
}