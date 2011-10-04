package scut.attmore.shengbo.ui;

import scut.attmore.shengbo.util.ReferenceManager;
import weibo4android.http.AccessToken;
import weibo4android.http.RequestToken;
import weibo4android.util.OAuthConstant;
import android.app.Activity;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.util.Log;
import android.widget.Toast;

public class OAuthCallBack extends Activity {
	private static String TAG = "OAuthCallBack";

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		Uri uri = this.getIntent().getData();
		try {
			RequestToken requestToken = OAuthConstant.getInstance()
					.getRequestToken();
			AccessToken accessToken = requestToken.getAccessToken(uri
					.getQueryParameter("oauth_verifier"));
			OAuthConstant.getInstance().setAccessToken(accessToken);
			if (accessToken != null) {
				Log.d(TAG, accessToken.getToken());
				Log.d(TAG, accessToken.getTokenSecret());
				ReferenceManager rm = ReferenceManager
						.getInstance(OAuthCallBack.this);
				rm.setWeiboToken(accessToken.getToken(), accessToken
						.getTokenSecret());
				rm.setFistRun(false);
				Toast.makeText(this, "认证成功", Toast.LENGTH_LONG).show();
				startActivity(new Intent(this, RecordingActivity.class));
			} else {
				Toast.makeText(this, "认证失败", Toast.LENGTH_LONG).show();
				startActivity(new Intent(this, RecordingActivity.class));
			}
		} catch (Exception e) {
			// TODO: handle exception
		}
	}
}
