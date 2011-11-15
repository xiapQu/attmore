/**
 * 
 */
package scut.attmore.shengbo.ui;

import java.io.File;
import java.io.IOException;

import scut.attmore.shengbo.R;
import scut.attmore.shengbo.recorder.ExtAudioRecorder;
import scut.attmore.shengbo.util.RandomUtil;
import scut.attmore.shengbo.util.ReferenceManager;
import scut.attmore.shengbo.util.SBUtil;
import scut.attmore.shengbo.view.FirstRunDialog;
import android.R.integer;
import android.content.Intent;
import android.media.MediaPlayer;
import android.os.Bundle;
import android.os.Environment;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.ProgressBar;
import android.widget.Toast;


/**
 * @author Administrator
 * 
 */
public class RecordingActivity extends BaseActivity {
	private Button btnStop, btnPlay, btnDelete, btnStart,
			btnBroadCast, btnSercet;
	private EditText edDescription;
	private ProgressBar mProgressBar;
	
	private File recordFile;
	private MediaPlayer mMediaPlayer;
	private ExtAudioRecorder mExtAudioRecorder;
	
	private String wavName = "";
	private int pattern = 0;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		
		setContentView(R.layout.recording);
		Bundle bd = getIntent().getExtras();
		pattern = bd.getInt("PATTERN");
		initComponent();

	}

	private void initComponent() {
		
		btnStop = (Button) findViewById(R.id.btnStop);
		btnPlay = (Button) findViewById(R.id.btnPlay);
		btnStart = (Button) findViewById(R.id.btnStart);
		btnDelete = (Button) findViewById(R.id.btnDelete);
		edDescription = (EditText) findViewById(R.id.recording_description);
		btnBroadCast = (Button) findViewById(R.id.btnBroadCast);
		mProgressBar = (ProgressBar) findViewById(R.id.play_progress_bar);

		btnDelete.setOnClickListener(mOnclickListener);
		btnPlay.setOnClickListener(mOnclickListener);
		btnStart.setOnClickListener(mOnclickListener);
		btnStop.setOnClickListener(mOnclickListener);
		btnBroadCast.setOnClickListener(mOnclickListener);

	}

	private void setAllInvisable() {
		btnDelete.setVisibility(View.GONE);
		btnPlay.setVisibility(View.GONE);
		btnStop.setVisibility(View.GONE);
		btnStart.setVisibility(View.GONE);
	}

	private OnClickListener mOnclickListener = new OnClickListener() {
		@Override
		public void onClick(View v) {
			switch (v.getId()) {
			
			case R.id.btnDelete:
				setAllInvisable();
				btnStart.setVisibility(View.VISIBLE);
				if (recordFile != null) {
					recordFile.delete();
				}
				recordFile = null;
				break;
			case R.id.btnPlay:
				mMediaPlayer = new MediaPlayer();
				try {
					mMediaPlayer.setDataSource(recordFile.getAbsolutePath());
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
				break;
			case R.id.btnStop:
				setAllInvisable();
				btnStart.setVisibility(View.VISIBLE);
				btnPlay.setVisibility(View.VISIBLE);
				btnDelete.setVisibility(View.VISIBLE);
				mExtAudioRecorder.stop();
				mExtAudioRecorder.release();
				Toast.makeText(RecordingActivity.this, "录音保存在/sdcard/shengbo目录下",
						Toast.LENGTH_SHORT).show();
				break;
			case R.id.btnStart:
				setAllInvisable();
				btnStop.setVisibility(View.VISIBLE);
				
				wavName = SBUtil.getFileName()+ "_" + RandomUtil.getRandomId();
				recordFile = new File(Environment.getExternalStorageDirectory()
						.getAbsoluteFile()
						+ "/shengbo/" + wavName + ".wav");
				mExtAudioRecorder = ExtAudioRecorder.getInstanse(true);
				mExtAudioRecorder.setOutputFile(recordFile.getAbsolutePath());
				mExtAudioRecorder.prepare();
				mExtAudioRecorder.start();
				break;
			// case R.id.btnSecret:
			// Intent intentSecret = new Intent(RecordingActivity.this,
			// SendSecretMessage.class);
			// intentSecret.putExtra("filepath", recordFile.getAbsolutePath());
			// intentSecret.putExtra("filename",recordFile.getName());
			// startActivity(intentSecret);
			// break;
			case R.id.btnBroadCast:
				String des = edDescription.getText().toString();
				if (recordFile == null) {
					Toast.makeText(RecordingActivity.this, "还没有录音呢",
							Toast.LENGTH_SHORT).show();
					return;
				}
				if (des.equals("")) {
					Toast.makeText(RecordingActivity.this, "描述一下录音吧",
							Toast.LENGTH_SHORT).show();
					return;
				}
				Intent intent = new Intent(RecordingActivity.this,SendBroadcastMessage.class);
				intent.putExtra("des",des);
				intent.putExtra("filename", recordFile.getName());
				intent.putExtra("filepath", recordFile.getAbsolutePath());
				intent.putExtra("wavname", wavName);
				intent.putExtra("pattern", pattern);
				RecordingActivity.this.startActivity(intent);
				break;
			default:
				break;
			}
		}
	};

}
