package scut.attmore.shengbo.ui;

import scut.attmore.shengbo.R;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.KeyEvent;
import android.webkit.WebSettings;
import android.webkit.WebView;

public class OAuthWebViewActivity extends Activity
{
	private WebView		mWebView;
	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		setContentView(R.layout.webview);
		mWebView = (WebView) findViewById(R.id.WebView01);
		
		WebSettings webSettings = mWebView.getSettings();  
		        
		webSettings.setJavaScriptEnabled(true);
		
		Bundle data=this.getIntent().getExtras();
		mWebView.loadUrl(data.getString("url"));

	}
	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		// TODO Auto-generated method stub
		
		if(keyCode==KeyEvent.KEYCODE_BACK){
			
			Intent it=new Intent();
			it.setClass(OAuthWebViewActivity.this, RecordingActivity.class);
			startActivity(it);
			OAuthWebViewActivity.this.finish();
			return true;
		}else{
			
			return super.onKeyDown(keyCode, event);
		}
	}
	
}
