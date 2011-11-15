/**
 * 
 */
package scut.attmore.shengbo.view;

import scut.attmore.shengbo.R;
import weibo4android.Weibo;
import weibo4android.WeiboException;
import weibo4android.http.RequestToken;
import weibo4android.util.OAuthConstant;
import android.app.Dialog;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

/**
 * @author Administrator
 * 
 */
public class FirstRunDialog extends Dialog {
	private Context context;
	private Button btnOk;
	public static String oauth_token_secret = "";
	public static String oauth_token = "";
	
	public FirstRunDialog(Context context) {
		super(context);
		this.context = context;
	}

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		setContentView(R.layout.first_run);
		System.setProperty("weibo4j.oauth.consumerKey", Weibo.CONSUMER_KEY);
		System.setProperty("weibo4j.oauth.consumerSecret", Weibo.CONSUMER_SECRET);
		btnOk = (Button) findViewById(R.id.first_run_btn);
		btnOk.setOnClickListener(mOncliClickListener);
	}

	private View.OnClickListener mOncliClickListener = new View.OnClickListener() {

		@Override
		public void onClick(View v) {
			// TODO Auto-generated method stub
			switch (v.getId()) {
			case R.id.first_run_btn: 
				Weibo weibo = OAuthConstant.getInstance().getWeibo();
            	RequestToken requestToken;
				try {
					requestToken = weibo.getOAuthRequestToken("shengbo://OAuthCallBack");
	    			Uri uri = Uri.parse(requestToken.getAuthenticationURL()+ "&from=xweibo");
	    			OAuthConstant.getInstance().setRequestToken(requestToken);
	    			context.startActivity(new Intent(Intent.ACTION_VIEW, uri));
	    			FirstRunDialog.this.dismiss();
				} catch (WeiboException e){
					e.printStackTrace();
				}
				break;
			default:
				break;
			}
		}
	};

}
