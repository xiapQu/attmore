package scut.attmore.shengbo.ui;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

import scut.attmore.shengbo.R;
import scut.attmore.shengbo.util.Act;
import scut.attmore.shengbo.util.Constants;
import scut.attmore.shengbo.util.ReferenceManager;
import scut.attmore.shengbo.util.SBUtil;
import weibo4android.Weibo;
import weibo4android.WeiboException;
import weibo4android.http.RequestToken;
import weibo4android.util.OAuthConstant;
import android.R.anim;
import android.app.ProgressDialog;
import android.content.Intent;
import android.content.SharedPreferences;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

public class SettingUI extends BaseActivity {

	private List<String> settinglist = null;
	private ProgressDialog dialog = null;
	private ListView settingListView;
	
	private String userName = "";
	
	@Override
	protected void onResume() {
		// TODO Auto-generated method stub
		super.onResume();
		
		final SharedPreferences setting = ReferenceManager.getInstance(
				SettingUI.this).getSetting();
		if ("".equals(setting.getString(Constants.USER_ID, ""))) {
			userName = "无";
		}else {
			userName = setting.getString("USERNAME", "");	
		}
			
		settinglist = new ArrayList<String>();
		settinglist.add("当前用户: "+ userName);
		settinglist.add("注销用户");
		settinglist.add("登陆用户");
		settinglist.add("清除录音图片记录");
		
		final ArrayAdapter<String> adapter = new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1, settinglist);
		
		settingListView.setAdapter(adapter);
		
		settingListView.setOnItemClickListener(new OnItemClickListener() {

			@Override
			public void onItemClick(AdapterView<?> arg0, View arg1, int position,
					long arg3) {
				switch (position) {
				case 1:
					ReferenceManager rm = ReferenceManager.getInstance(SettingUI.this);
					rm.setFistRun(true);
					setting.edit()
						.remove(Constants.USER_ID)
						.remove(Constants.ACCESS_TOKEN_KEY)
						.remove(Constants.ACCESS_TOKEN_SECRET)
						.putBoolean(Constants.USER_QUIT, true)
						.commit();
					Toast.makeText(getApplicationContext(), "用户已注销,请注意重新登录新用户", Toast.LENGTH_SHORT).show();
					adapter.notifyDataSetChanged();
					break;
				case 2:
					if (setting.getBoolean(Constants.USER_QUIT, false)) {
						System.setProperty("weibo4j.oauth.consumerKey",
								Weibo.CONSUMER_KEY);
						System.setProperty("weibo4j.oauth.consumerSecret",
								Weibo.CONSUMER_SECRET);
						
						dialog.show();
						
						new Thread(){
							@Override
							public void run() {
								super.run();
								
								Weibo weibo = OAuthConstant.getInstance().getWeibo();
				            	RequestToken requestToken;
								try {
									requestToken = weibo.getOAuthRequestToken("shengbo://OAuthCallBack");
					    			Uri uri = Uri.parse(requestToken.getAuthenticationURL()+ "&from=xweibo");
					    			OAuthConstant.getInstance().setRequestToken(requestToken);
					    			startActivity(new Intent(Intent.ACTION_VIEW, uri));
					    			Message message = new Message();
									message.what = 0;
									mHandler.sendMessage(message);
								} catch (WeiboException e){
									e.printStackTrace();
								}
							}
						}.start();
					}else {
						Toast.makeText(getApplicationContext(), "该用户未注销,请先注销后登陆", Toast.LENGTH_SHORT).show();
					}
					
					
					break;
				case 3:
					try {
						String rootPath = SBUtil.getSDPath() + "/shengbo/";
						File f = new File(rootPath);
						File[] files = f.listFiles();
						for (int i = 0; i < files.length; i++) {
							files[i].delete();
						}
						Toast.makeText(getApplicationContext(), "清除完毕", Toast.LENGTH_SHORT).show();
					} catch (Exception e) {
						Toast.makeText(getApplicationContext(), "清除失败", Toast.LENGTH_SHORT).show();
					}					
					break;
				default:
					break;
				}
			}
		});
	}
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);		
		setContentView(R.layout.setting_ui);
		
		Act.add(SettingUI.this);
		
		TextView textView = (TextView) findViewById(R.id.setting_tv);
		settingListView = (ListView) findViewById(R.id.setting_list);
		
		dialog = new ProgressDialog(SettingUI.this);
		dialog.setMessage("用户登录中...");
		dialog.setIndeterminate(false);
		dialog.setCancelable(true);
		
	}
	
	private Handler mHandler = new Handler() {
		@Override
		public void handleMessage(Message msg) {
			if (msg.what == 0) {
				if (dialog!=null) {
					dialog.dismiss();
				}
			}	
		}
	};
	
}
