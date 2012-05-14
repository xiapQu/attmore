package scut.attmore.ui;

import scut.attmore.ui.R;
import scut.attmore.ui.view.RadioButtonEx;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.Toast;
import android.widget.CompoundButton.OnCheckedChangeListener;

public class MainAppActivity extends Activity {
	/** Called when the activity is first created. */
	private RadioButtonEx radioButtonEx = null;
	private Button btnTestPanelSwitcher=null,btnTestDashboard=null;
	private View.OnClickListener mOnClickListener=new View.OnClickListener() {
		@Override
		public void onClick(View v) {
			switch(v.getId()){
			case R.id.btnDashborad:
				Intent testTempDashboard=new Intent(MainAppActivity.this,TestTempDashboard.class);
				MainAppActivity.this.startActivity(testTempDashboard);
				break;
			}
		}
	};
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);
		btnTestDashboard=(Button)findViewById(R.id.btnDashborad);
		btnTestDashboard.setOnClickListener(mOnClickListener);
		
		radioButtonEx = (RadioButtonEx) findViewById(R.id.radioButtomEx);
		radioButtonEx.setValues("nice");
		radioButtonEx.setOnCheckedChangeListener(new OnCheckedChangeListener() {
			@Override
			public void onCheckedChanged(CompoundButton buttonView,
					boolean isChecked) {
				Toast.makeText(MainAppActivity.this, radioButtonEx.getValues(),
						Toast.LENGTH_LONG).show();
				
			}
		});
	}
}