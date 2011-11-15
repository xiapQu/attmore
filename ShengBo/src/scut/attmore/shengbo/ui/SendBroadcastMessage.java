package scut.attmore.shengbo.ui;

import java.io.File;
import java.util.HashMap;
import java.util.Map;

import scut.attmore.shengbo.R;
import scut.attmore.shengbo.net.FormFile;
import scut.attmore.shengbo.net.SocketHttpRequester;
import scut.attmore.shengbo.util.Act;
import scut.attmore.shengbo.util.Constants;
import scut.attmore.shengbo.util.RandomUtil;
import scut.attmore.shengbo.util.ReferenceManager;
import scut.attmore.shengbo.util.SBUtil;
import weibo4android.Weibo;
import android.app.Activity;
import android.app.ProgressDialog;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Color;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.provider.MediaStore;
import android.text.Editable;
import android.text.TextWatcher;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

public class SendBroadcastMessage extends BaseActivity {

	private String filepath;
	private String filename;
	private String wavname = "temp";
	private String des;
	private String photopath;
	private String mText = "";
	
	private int pattern = 0;

	private TextView mTextNum;
	private Button mSend, mTake;
	private ImageView img;
	private EditText mEdit;
	private ProgressDialog dialog = null;
	private Bitmap bm;

	private Handler mHandler = new Handler() {
		@Override
		public void handleMessage(Message msg) {
			// TODO Auto-generated method stub
			switch (msg.what) {
			// upload ok
			case 0:
				Toast.makeText(SendBroadcastMessage.this, "上传语音成功",
						Toast.LENGTH_SHORT).show();
				break;
			// upload error
			case 1:			
				Toast.makeText(SendBroadcastMessage.this, "上传语音失败",
						Toast.LENGTH_SHORT).show();
				break;
			// update ok
			case 2:
				if (dialog!=null) {
					dialog.dismiss();
				}
				Toast.makeText(SendBroadcastMessage.this, "发布成功",
						Toast.LENGTH_SHORT).show();
				TextSave();
				SendResultSave(true);
				if (bm != null) {
					bm.recycle();
				}
				SendBroadcastMessage.this.finish();
				break;
			// update error
			case 3:
				if (dialog!=null) {
					dialog.dismiss();
				}
				TextSave();
				SendResultSave(false);
				Toast.makeText(SendBroadcastMessage.this, "发布失败",
						Toast.LENGTH_SHORT).show();
				if (bm != null) {
					bm.recycle();
				}
				SendBroadcastMessage.this.finish();
				break;
				
			default:
				break;
			}

		}

	};

	private OnClickListener mOnClickListener = new View.OnClickListener() {

		@Override
		public void onClick(View v) {
			// TODO Auto-generated method stub
			switch (v.getId()) {
			case R.id.btnSend:
				System.setProperty("weibo4j.oauth.consumerKey",
						Weibo.CONSUMER_KEY);
				System.setProperty("weibo4j.oauth.consumerSecret",
						Weibo.CONSUMER_SECRET);
				
				dialog.show();
				
				new Thread() {
					@Override
					public void run() {
						// TODO Auto-generated method stub
						super.run();
						Map<String, String> params = new HashMap<String, String>();
						params.put("des", mEdit.getText().toString());
						params.put("pwd", "0");
						params.put("isPwd", "0");
						File uploadFile = new File(filepath);
						FormFile formfile = new FormFile(filename, uploadFile,
								"file", "audio/mpeg");
						try {
							if (SocketHttpRequester.post(
									"http://shengbo.sinaapp.com/update.php",
									params, formfile)) {
								// ok
								Message message = new Message();
								message.what = 0;
								mHandler.sendMessage(message);
							} else {
								// error
								Message message = new Message();
								message.what = 1;
								mHandler.sendMessage(message);
							}
						} catch (Exception e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
							// error
						}
					}
				}.start();
				new Thread() {
					@Override
					public void run() {
						// TODO Auto-generated method stub
						super.run();
						try {
							Weibo weibo = new Weibo();
							SharedPreferences setting = ReferenceManager.getInstance(
									SendBroadcastMessage.this).getSetting();
							weibo.setToken(setting.getString(
									Constants.ACCESS_TOKEN_KEY, ""), setting.getString(
									Constants.ACCESS_TOKEN_SECRET, ""));
							if( bm != null ){
								File f = new File(photopath);
								weibo.uploadStatus(mEdit.getText().toString()+" http://shengbo.sinaapp.com/voice.php?file="+filename, f);
							}else{
								weibo.updateStatus(mEdit.getText().toString()+" http://shengbo.sinaapp.com/voice.php?file="+filename);//FIXME 这里要加上地址
							}
							Message msg = new Message();
							msg.what = 2;
							mHandler.sendMessage(msg);
						} catch (Exception e) {
							e.printStackTrace();
							Message msg = new Message();
							msg.what = 3;
							mHandler.sendMessage(msg);
						}
					}
				}.start();
				break;
			case R.id.btnClose:
				TextSave();
				SendBroadcastMessage.this.finish();				
				break;
			case R.id.btnPhoto:
				TextSave();
				Intent intent1 = new Intent("android.media.action.IMAGE_CAPTURE");
				intent1.putExtra( MediaStore.EXTRA_OUTPUT, Uri.fromFile(new File(photopath)));
				startActivityForResult( intent1, Activity.DEFAULT_KEYS_DIALER);
				break;
			default:
				break;
			}
		}
	};

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		
		Act.add(SendBroadcastMessage.this);
		
		dialog = new ProgressDialog(SendBroadcastMessage.this);
		dialog.setMessage("声博发送中...");
		dialog.setIndeterminate(false);
		dialog.setCancelable(true);
		
		setContentView(R.layout.broad_cast_message);
		Bundle bd = getIntent().getExtras();
		pattern = bd.getInt("pattern");
		filepath = bd.getString("filepath");
		filename = bd.getString("filename");
		wavname = bd.getString("wavname");
		des = bd.getString("des");
		Log.d("Message", filepath);
		Log.d("Message", filename);
		Log.d("Message", des);
		initComponent();
		
		photopath = SBUtil.getCamerePath() + wavname + ".bmp";
		PhotoShow(0);
		
		switch (pattern) {
		case 1:
			mEdit.setText("#声博##雷锋的约定# " + des);
			break;
		case 2:
			mEdit.setText("#声博##我要爆料# @sword5307 @G_gets @糯米_炜 " + des);
			break;
		case 3:
			mEdit.setText("#声博##微博留声机# " + des);
			break;

		default:
			mEdit.setText("#声博# " + des);
			break;
		}
		
	}

	/**
	 * init component of the view
	 */
	private void initComponent() {
		Button close = (Button) this.findViewById(R.id.btnClose);
		close.setOnClickListener(mOnClickListener);
		mSend = (Button) this.findViewById(R.id.btnSend);
		mTake = (Button) this.findViewById(R.id.btnPhoto);
		mSend.setOnClickListener(mOnClickListener);
		mTake.setOnClickListener(mOnClickListener);
		mTextNum = (TextView) this.findViewById(R.id.tv_text_limit);
		mEdit = (EditText) this.findViewById(R.id.etEdit);
		img = (ImageView)findViewById(R.id.photo_take);
		mEdit.addTextChangedListener(new TextWatcher() {

			@Override
			public void onTextChanged(CharSequence s, int start, int before,
					int count) {
				// TODO Auto-generated method stub
				mText = mEdit.getText().toString();
				int len = mText.length();
				if (len <= 140) {
					len = 140 - len;
					mTextNum.setTextColor(R.color.dark_blue);
					if (!mSend.isEnabled())
						mSend.setEnabled(true);
				} else {
					len = len - 140;
					mTextNum.setTextColor(Color.RED);
					if (mSend.isEnabled())
						mSend.setEnabled(false);
				}
				mTextNum.setText(String.valueOf(len));
			}

			@Override
			public void beforeTextChanged(CharSequence s, int start, int count,
					int after) {
				// TODO Auto-generated method stub

			}

			@Override
			public void afterTextChanged(Editable s) {
				// TODO Auto-generated method stub

			}
		});
	}
	
	@Override 
	protected void onActivityResult(int requestCode, int resultCode, Intent data)
	{ 
		if( requestCode == Activity.DEFAULT_KEYS_DIALER ){
			if ( resultCode == RESULT_OK ) {
			     PhotoShow(1);
			}
		}
		super.onActivityResult(requestCode, resultCode, data); 		
	}
	
	private void PhotoShow(int pat){
		try{
			File f = new File(photopath);
			if(f.exists()){
				bm = BitmapFactory.decodeFile(photopath);
				img.setImageBitmap(bm);
			}else {
				if (pat == 1) {
					Toast.makeText(this, "无法打开该图片", Toast.LENGTH_SHORT).show();
				}				
			}
	     }
		catch(Exception e){
				
		}
	}
	
	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		if (keyCode == KeyEvent.KEYCODE_BACK) {
			TextSave();
		}
		return super.onKeyDown(keyCode, event);
	}
	
	private void TextSave(){
		String tempString = "";
		switch (pattern) {
		case 1:
			tempString = mText.substring(12, mText.length());
			break;
		case 2:
			tempString = mText.substring(36, mText.length());
			break;
		case 3:
			tempString = mText.substring(12, mText.length());
			break;
		default:
			tempString = mText.substring(5, mText.length());
			break;
		}
		SharedPreferences setting = ReferenceManager.getInstance(
				this).getSetting();
		setting.edit().putString(wavname, tempString).commit();
	}
	
	private void SendResultSave(Boolean boolean1){
		SharedPreferences setting = ReferenceManager.getInstance(
				this).getSetting();
		setting.edit().putBoolean(filename, boolean1).commit();
	}
}
