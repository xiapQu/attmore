package scut.attmore.audio;

import android.app.Activity;
import android.media.AudioFormat;
import android.media.AudioManager;
import android.media.AudioTrack;
import android.os.Bundle;
import android.os.Handler;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

public class AudioTestOneActivity extends Activity {
	private final int duration = 25; // seconds
	private final int sampleRate = 48000; // 每秒采样多少次
	private final int numSamples = duration * sampleRate;
	private final double sample[] = new double[numSamples];
	private final double freqOfTone = 8000; // hz 声音的频率

	private final byte generatedSnd[] = new byte[2 * numSamples];

	Handler handler = new Handler();

	private Button send, stop;
	private View.OnClickListener mOnClickListener = new OnClickListener() {

		@Override
		public void onClick(View v) {
			// TODO Auto-generated method stub
			switch (v.getId()) {
			case R.id.send:
				// Use a new tread as this can take a while
				Thread thread = new Thread(new Runnable() {
					public void run() {
						genTone();
						handler.post(new Runnable() {

							public void run() {
								playSound();
							}
						});
					}
				});
				thread.start();
				break;
			case R.id.stop:
				break;
			}
		}
	};

	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);
		send = (Button) findViewById(R.id.send);
		stop = (Button) findViewById(R.id.stop);
		send.setOnClickListener(mOnClickListener);
		stop.setOnClickListener(mOnClickListener);
	}

	@Override
	protected void onResume() {
		super.onResume();
	}

	/*
	 * 生成波形这里好复杂 操！！ 这里生成了一个正弦波
	 */
	void genTone() {
		// fill out the array
		for (int i = 0; i < numSamples; ++i) {
//			 sample[i] = Math.sin(2 * Math.PI * i / (sampleRate /
//			 freqOfTone));
//			if (i % (sampleRate /freqOfTone) < 1)
			if (i % (sampleRate /freqOfTone) < (sampleRate /freqOfTone)/2)
				sample[i] = 1;
			else
				sample[i] = 0;
		}

		// convert to 16 bit pcm sound array
		// assumes the sample buffer is normalised.
		int idx = 0;
		for (double dVal : sample) {
			short val = (short) (dVal * 32767);
			generatedSnd[idx++] = (byte) (val & 0x00ff);
			generatedSnd[idx++] = (byte) ((val & 0xff00) >>> 8);
		}
	}

	void playSound() {
		AudioTrack audioTrack = new AudioTrack(AudioManager.STREAM_MUSIC,
				sampleRate, AudioFormat.CHANNEL_CONFIGURATION_MONO,
				AudioFormat.ENCODING_PCM_16BIT, numSamples,
				AudioTrack.MODE_STATIC);
		audioTrack.write(generatedSnd, 0, numSamples);
		audioTrack.setStereoVolume(1, 1);
		audioTrack.play();
	}

}