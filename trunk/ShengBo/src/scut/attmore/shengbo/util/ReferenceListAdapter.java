package scut.attmore.shengbo.util;

import java.io.IOException;
import java.util.List;

import scut.attmore.shengbo.R;
import scut.attmore.shengbo.R.color;
import scut.attmore.shengbo.ui.RecordingActivity;
import scut.attmore.shengbo.ui.ReferenceUI;
import scut.attmore.shengbo.ui.SendBroadcastMessage;

import android.app.AlertDialog.Builder;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.res.ColorStateList;
import android.graphics.Color;
import android.media.MediaPlayer;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

public class ReferenceListAdapter extends BaseAdapter {

	private Context context;
	private List<String> itemsList;
	private List<String> pathsList;
	private List<Boolean> judgementList;
	private Builder builder; //发送类型选择对话框
	private Builder builder2; //是否再次发送对话框
	private LayoutInflater mInflater;
	private MediaPlayer mMediaPlayer;
	
	public ReferenceListAdapter(Context _context, List<String> _itemsList, List<String> _pathsList, Builder _builder,
			Builder _builder2, List<Boolean> _judgementList){
		context = _context;
		itemsList = _itemsList;
		pathsList = _pathsList;
		builder = _builder;
		builder2 = _builder2;
		judgementList = _judgementList;
		
		mInflater = (LayoutInflater) _context
		.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
	}
	
	@Override
	public int getCount() {
		if (itemsList != null) {
			return itemsList.size();
		}
		return 0;
	}

	@Override
	public Object getItem(int arg0) {
		if (itemsList != null) {
			return itemsList.get(arg0);
		}
		return null;
	}

	@Override
	public long getItemId(int arg0) {
		return arg0;
	}

	@Override
	public View getView(int arg, View convertView, ViewGroup parent) {
		final int position = arg;
		
		convertView = mInflater.inflate(scut.attmore.shengbo.R.layout.filerow, null);
		
		String itemName = itemsList.get(position);
		
		TextView wavNametv = (TextView) convertView.findViewById(R.id.reference_text);
		Button btnButton = (Button) convertView.findViewById(R.id.reference_button);
		
		if ( judgementList.get(position) == true ) {
			btnButton.setText("已发送");
			btnButton.setBackgroundResource(R.drawable.btn_blue);
			btnButton.setTextColor(scut.attmore.shengbo.R.color.dark_blue);
			
			btnButton.setOnClickListener(new OnClickListener() {
				
				@Override
				public void onClick(View arg0) {
					ReferenceUI.position = position;
					builder2.show();
				}
			});
		}else {
			btnButton.setOnClickListener(new OnClickListener() {
				
				@Override
				public void onClick(View arg0) {
					ReferenceUI.position = position;
					builder.show();
				}
			});
		}
		
		wavNametv.setText(itemName);
	
		wavNametv.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View arg0) {
				mMediaPlayer = new MediaPlayer();
				try {
					mMediaPlayer.setDataSource(pathsList.get(position));
					mMediaPlayer.prepare();
				} catch (IllegalArgumentException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} catch (IllegalStateException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				// mProgressBar.setVisibility(View.VISIBLE);
				// mProgressBar.setMax(mMediaPlayer.getDuration());
				mMediaPlayer.start();
			}
		});
		
		return convertView;
	}
	
}
