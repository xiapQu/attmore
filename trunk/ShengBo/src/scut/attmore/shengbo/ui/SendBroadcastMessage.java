package scut.attmore.shengbo.ui;

import java.io.File;
import java.util.HashMap;
import java.util.Map;

import scut.attmore.shengbo.R;
import scut.attmore.shengbo.net.FormFile;
import scut.attmore.shengbo.net.SocketHttpRequester;
import scut.attmore.shengbo.util.Constants;
import scut.attmore.shengbo.util.ReferenceManager;
import weibo4android.Weibo;
import android.app.ProgressDialog;
import android.content.SharedPreferences;
import android.graphics.Color;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.text.Editable;
import android.text.TextWatcher;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class SendBroadcastMessage extends BaseActivity {
	private String filepath;
	private String filename;
	private String des;

	private TextView mTextNum;
	private Button mSend;
	private EditText mEdit;
	private ProgressDialog mProgressDialog;

	private Handler mHandler = new Handler() {
		@Override
		public void handleMessage(Message msg) {
			// TODO Auto-generated method stub
			switch (msg.what) {
			// ok
			case 0:
				Toast.makeText(SendBroadcastMessage.this, "上传语音成功",
						Toast.LENGTH_LONG).show();
				break;
			// error
			case 1:
				Toast.makeText(SendBroadcastMessage.this, "上传语音失败",
						Toast.LENGTH_LONG).show();
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
				}.run();
				try {
					Weibo weibo = new Weibo();
					SharedPreferences setting = ReferenceManager.getInstance(
							SendBroadcastMessage.this).getSetting();
					weibo.setToken(setting.getString(
							Constants.ACCESS_TOKEN_KEY, ""), setting.getString(
							Constants.ACCESS_TOKEN_SECRET, ""));
					weibo.updateStatus(mEdit.getText().toString()+"http://shengbo.sinaapp.com/voice.php?file="+filename);//FIXME 这里要加上地址
					Toast.makeText(SendBroadcastMessage.this, "发布成功",
							Toast.LENGTH_LONG).show();
					SendBroadcastMessage.this.finish();
				} catch (Exception e) {
					e.printStackTrace();
					Toast.makeText(SendBroadcastMessage.this, "发布成功",
							Toast.LENGTH_LONG).show();
					SendBroadcastMessage.this.finish();
				}
				break;
			case R.id.btnClose:
				SendBroadcastMessage.this.finish();
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
		setContentView(R.layout.broad_cast_message);
		Bundle bd = getIntent().getExtras();
		filepath = bd.getString("filepath");
		filename = bd.getString("filename");
		des = bd.getString("des");
		Log.d("Message", filepath);
		Log.d("Message", filename);
		Log.d("Message", des);
		initComponent();
		mEdit.setText("#声博#" + des);
	}

	/**
	 * init component of the view
	 */
	private void initComponent() {
		Button close = (Button) this.findViewById(R.id.btnClose);
		close.setOnClickListener(mOnClickListener);
		mSend = (Button) this.findViewById(R.id.btnSend);
		mSend.setOnClickListener(mOnClickListener);
		mTextNum = (TextView) this.findViewById(R.id.tv_text_limit);
		mEdit = (EditText) this.findViewById(R.id.etEdit);
		mEdit.addTextChangedListener(new TextWatcher() {

			@Override
			public void onTextChanged(CharSequence s, int start, int before,
					int count) {
				// TODO Auto-generated method stub
				String mText = mEdit.getText().toString();
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
}
