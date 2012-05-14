/**
 * author : Administrator
 * date   : 2012-4-2
 * file   : TempDashboard.java
 * prj    : CustomComponents
 * usefor : 
 */
package scut.attmore.ui.view;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.LinearGradient;
import android.graphics.Paint;
import android.graphics.RectF;
import android.graphics.Shader;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.util.AttributeSet;
import android.util.Log;
import android.view.View;
import android.view.View.MeasureSpec;

/**
 * @author Administrator
 *
 */
public class TempDashboard extends View implements SensorEventListener {
	private RectF dbRimRect=null;
	private Paint dbRimPaint=null;
	public TempDashboard(Context context){
		super(context);
		init();
	}
	
	public TempDashboard(Context context,AttributeSet attrs,int defSytle){
		super(context, attrs, defSytle);
		init();
	}
	
	public TempDashboard(Context context, AttributeSet attrs) {
		super(context, attrs);
		init();
		
	}
	
	/**
	 * 得到控件的大小
	 * 这里让长和宽相同
	 */
	@Override
	protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
		int widthMode = MeasureSpec.getMode(widthMeasureSpec);
		int widthSize = MeasureSpec.getSize(widthMeasureSpec);
		
		int heightMode = MeasureSpec.getMode(heightMeasureSpec);
		int heightSize = MeasureSpec.getSize(heightMeasureSpec);
		
		int chosenWidth = chooseDimension(widthMode, widthSize);
		int chosenHeight = chooseDimension(heightMode, heightSize);
		
		int chosenDimension = Math.min(chosenWidth, chosenHeight);
		
		setMeasuredDimension(chosenDimension, chosenDimension);
	}
	
	private int chooseDimension(int mode, int size) {
		if (mode == MeasureSpec.AT_MOST || mode == MeasureSpec.EXACTLY) {
			return size;
		} else { // (mode == MeasureSpec.UNSPECIFIED)
			return 300; //default size
		} 
	}
	
	private void init(){
		dbRimRect = new RectF(0.1f, 0.1f, 0.9f, 0.9f);
		dbRimPaint=new Paint(Paint.ANTI_ALIAS_FLAG);//抗锯齿
		dbRimPaint.setShader(new LinearGradient(0.40f, 0.0f, 0.60f, 1.0f, 
				   Color.rgb(0xf0, 0xf5, 0xf0),
				   Color.rgb(0x30, 0x31, 0x30),
				   Shader.TileMode.CLAMP));
		
	}
	
	@Override
	protected void onDraw(Canvas canvas) {
		
		canvas.save(Canvas.MATRIX_SAVE_FLAG);
		canvas.drawOval(dbRimRect, dbRimPaint);
		canvas.restore();
		super.onDraw(canvas);
	}
	
	
	/* (non-Javadoc)
	 * @see android.hardware.SensorEventListener#onSensorChanged(android.hardware.SensorEvent)
	 */
	@Override
	public void onSensorChanged(SensorEvent event) {
		// TODO Auto-generated method stub

	}

	/* (non-Javadoc)
	 * @see android.hardware.SensorEventListener#onAccuracyChanged(android.hardware.Sensor, int)
	 */
	@Override
	public void onAccuracyChanged(Sensor sensor, int accuracy) {
		// TODO Auto-generated method stub

	}

}
