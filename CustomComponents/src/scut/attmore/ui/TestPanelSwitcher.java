/**
 * author : Administrator
 * date   : 2012-4-2
 * file   : TestPanelSwitcher.java
 * prj    : CustomComponents
 * usefor : 
 */
package scut.attmore.ui;

import android.app.Activity;
import android.graphics.Color;
import android.os.Bundle;
import android.widget.LinearLayout;

/**
 * @author Administrator
 * 
 */
public class TestPanelSwitcher extends Activity {
	private LinearLayout mFirstLayout;
	private LinearLayout mSecondLayout;
	private LinearLayout mThirdLayout;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		setContentView(R.layout.panel_switcher);
		mFirstLayout = (LinearLayout) findViewById(R.id.panel1);
		mSecondLayout = (LinearLayout) findViewById(R.id.panel2);
		mThirdLayout = (LinearLayout) findViewById(R.id.panel3);
		mFirstLayout.setBackgroundColor(Color.RED);
		mSecondLayout.setBackgroundColor(Color.BLUE);
		mThirdLayout.setBackgroundColor(Color.GREEN);
	}

}
