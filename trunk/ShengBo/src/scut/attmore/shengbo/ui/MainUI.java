package scut.attmore.shengbo.ui;

import java.io.File;

import scut.attmore.shengbo.R;
import scut.attmore.shengbo.util.Act;
import scut.attmore.shengbo.util.Constants;
import scut.attmore.shengbo.util.ReferenceManager;
import scut.attmore.shengbo.view.FirstRunDialog;
import weibo4android.User;
import weibo4android.Weibo;
import weibo4android.WeiboException;
import android.app.Activity;
import android.app.AlertDialog;
import android.app.AlertDialog.Builder;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.view.Window;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

public class MainUI extends BaseActivity {

	private Button btnAbout, btnSetting, btn1, btn2, btn3, btn4;
	private TextView idshowtv;
	private int pattern = 0;
	private String userName = "无";
	private String userId = "";
	private ImageView imgAbout, imgSetting;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
			
		super.onCreate(savedInstanceState);	
		setContentView(R.layout.main_ui);
		
		Act.init();
		Act.add(MainUI.this);
		
		if (ReferenceManager.getInstance(this).isFirstRun()) {
			File file = new File(Environment.getExternalStorageDirectory()
					+ "/shengbo");
			if (!file.exists()) {
				file.mkdir();
			}
			FirstRunDialog frd = new FirstRunDialog(this);
			frd.setCancelable(true);
			frd.setTitle("提示");
			frd.show();
		}
		
		initComponent();
	}

	@Override
	protected void onResume() {
		// TODO Auto-generated method stub
		super.onResume();
		SharedPreferences setting = ReferenceManager.getInstance(
				MainUI.this).getSetting();
		String temp = setting.getString(Constants.CURRENT_USER_ID, "");
		if ( setting.getString(Constants.USER_ID, "").equals(temp) && ( "".equals(temp) != true )) {
			userName = setting.getString("USERNAME", "");
			idshowtv.setText("当前用户: "+userName);
		}else {
			if ("".equals(setting.getString(Constants.USER_ID, ""))) {
				idshowtv.setText("当前用户: 无");
			}else {
				idshowtv.setText("正在获取用户名.");
				Thread thread = new Thread( new UserGetThread( MainUI.this ) );
				thread.start();
			}
		}
	}
	
	private void initComponent() {

		imgAbout = (ImageView) findViewById(R.id.img_about_2);
		imgSetting = (ImageView) findViewById(R.id.img_setting_2);
		
		idshowtv = (TextView) findViewById(R.id.idshow);
		btnAbout = (Button) findViewById(R.id.btn_about_2);
		btnSetting = (Button) findViewById(R.id.btn_setting_2);
		btn1 = (Button) findViewById(R.id.promiss);
		btn2 = (Button) findViewById(R.id.baoliao);
		btn3 = (Button) findViewById(R.id.phonograph);
		btn4 = (Button) findViewById(R.id.reference);
		
		imgAbout.setOnClickListener(mOnclickListener);
		imgSetting.setOnClickListener(mOnclickListener);
		btnAbout.setOnClickListener(mOnclickListener);
		btnSetting.setOnClickListener(mOnclickListener);
		btn1.setOnClickListener(mOnclickListener);
		btn2.setOnClickListener(mOnclickListener);
		btn3.setOnClickListener(mOnclickListener);
		btn4.setOnClickListener(mOnclickListener);
	
	}
	
	private OnClickListener mOnclickListener = new OnClickListener() {

		@Override
		public void onClick(View v) {
			switch (v.getId()) {
			case R.id.img_about_2:
			case R.id.btn_about_2:
				AlertDialog.Builder builder = new Builder(MainUI.this);
				builder.setTitle("关于我们");
				builder.setMessage("本软件由华南理工大学计算机学院与非门团队开发");
				builder.create().show();
				break;
			case R.id.img_setting_2:
			case R.id.btn_setting_2:
				Intent intent = new Intent(MainUI.this, SettingUI.class);
				startActivity(intent);
				break;
			case R.id.promiss:
				pattern = 1;
				GoToIntent(pattern);
				break;	
			case R.id.baoliao:
				pattern = 2;
				GoToIntent(pattern);
				break;	
			case R.id.phonograph:
				pattern = 3;
				GoToIntent(pattern);
				break;	
			case R.id.reference:
				GoToIntent();
				break;		
			}
		}
		
	};
	
	private void GoToIntent(int pattern){
		Intent intent = new Intent( MainUI.this, RecordingActivity.class);
		Bundle bundle = new Bundle();
		bundle.putInt("PATTERN", pattern);
		intent.putExtras(bundle);
		startActivity(intent);
	}
	
	private void GoToIntent(){
		Intent intent = new Intent( MainUI.this, ReferenceUI.class);
		startActivity(intent);
	}
	
	class UserGetThread implements Runnable{

		Context context;
		
		public UserGetThread(Context _context) {
			context = _context;
		}
		
		@Override
		public void run() {
			Weibo weibo = new Weibo();
			SharedPreferences setting = ReferenceManager.getInstance(
					context).getSetting();
			weibo.setToken(setting.getString(
					Constants.ACCESS_TOKEN_KEY, ""), setting.getString(
					Constants.ACCESS_TOKEN_SECRET, ""));
			userId = setting.getString(Constants.USER_ID, "");
            try {
				User user = weibo.showUser(userId);
				userName = user.getScreenName();
				setting.edit()
					.putString(Constants.CURRENT_USER_ID, userId)
					.putString(Constants.USER_NAME, userName)
					.commit();
			} catch (WeiboException e) {
				e.printStackTrace();
            	Log.e("Weibo", e.getMessage());
			}
			handle.sendEmptyMessage(0);
		}
	}
	
	Handler handle = new Handler(){
		@Override
		public void handleMessage(Message msg)
		{		
			idshowtv.setText("当前用户: "+userName);
		}
	};
	
	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		if (keyCode == KeyEvent.KEYCODE_BACK) {
			Act.delete();
		}
		return super.onKeyDown(keyCode, event);
	}
}
